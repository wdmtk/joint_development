#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DATA.h"
#define BUF_SIZE 256 // 一行の最大文字数(バイト数)


typedef struct {
    char countryName[BUF_SIZE];
    int medalRank;
    int medalGetNum;
} object; //オブジェクト型して、定義

struct COUNTRY_DATA {
    int medalRank;
    char countryName[BUF_SIZE];
    int goldMedal;
    int silverMedal;
    int bronzeMedal;
    int totalMedal;
};

void fileWrite(char *countryName, int goldMedal, int silverMedal, int copperMedal) {
    FILE *fp;

    char *fname = "data.csv";

    fp = fopen("data.csv", "a");

    if(fp == NULL) {
        printf("Error: 書き込むファイルが見つかりませんでした。");
        exit(0);
    }
    char inputString[BUF_SIZE];

    sprintf(inputString, "%s,%d,%d,%d\n", countryName, goldMedal, silverMedal, copperMedal);
    fputs(inputString, fp);

    fclose(fp);
}

struct COUNTRY_DATA* main() {
    FILE *fp;
    char *fileName = "data.csv";
    static struct COUNTRY_DATA data[BUF_SIZE];
    static struct COUNTRY_DATA *data_p = data;
    char tmpString[BUF_SIZE];
    char countryName[BUF_SIZE];
    int goldMedal;
    int silverMedal;
    int bronzeMedal;

    fp = fopen(fileName, "r");
    if(fp==NULL) {
        printf("Error: 読み込むファイルが見つかりませんでした。");
        exit(1);
    }else {
        for(int i=0; fgets(tmpString, BUF_SIZE, fp)!=NULL; i++) {
            sscanf(tmpString, "%[^,],%d,%d,%d", countryName, &goldMedal, &silverMedal, &bronzeMedal);
            data[i] = init_data(i+1, countryName, goldMedal, silverMedal, bronzeMedal);
        }
    }
    fclose(fp);

    return data_p;
}