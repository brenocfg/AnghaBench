#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int KEY_TEST_NUM ; 
 unsigned int NUM_TESTS ; 
 char* cbc_data ; 
 int* cbc_iv ; 
 int* cbc_key ; 
 int* cbc_ok ; 
 int* cfb64_ok ; 
 int** cipher_data ; 
 int** ecb_data ; 
 int* key_data ; 
 int** key_out ; 
 int* key_test ; 
 int* ofb64_ok ; 
 int** plain_data ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int print_test_data(void)
{
    unsigned int i, j;

    printf("ecb test data\n");
    printf("key bytes\t\tclear bytes\t\tcipher bytes\n");
    for (i = 0; i < NUM_TESTS; i++) {
        for (j = 0; j < 8; j++)
            printf("%02X", ecb_data[i][j]);
        printf("\t");
        for (j = 0; j < 8; j++)
            printf("%02X", plain_data[i][j]);
        printf("\t");
        for (j = 0; j < 8; j++)
            printf("%02X", cipher_data[i][j]);
        printf("\n");
    }

    printf("set_key test data\n");
    printf("data[8]= ");
    for (j = 0; j < 8; j++)
        printf("%02X", key_data[j]);
    printf("\n");
    for (i = 0; i < KEY_TEST_NUM - 1; i++) {
        printf("c=");
        for (j = 0; j < 8; j++)
            printf("%02X", key_out[i][j]);
        printf(" k[%2u]=", i + 1);
        for (j = 0; j < i + 1; j++)
            printf("%02X", key_test[j]);
        printf("\n");
    }

    printf("\nchaining mode test data\n");
    printf("key[16]   = ");
    for (j = 0; j < 16; j++)
        printf("%02X", cbc_key[j]);
    printf("\niv[8]     = ");
    for (j = 0; j < 8; j++)
        printf("%02X", cbc_iv[j]);
    printf("\ndata[%d]  = '%s'", (int)strlen(cbc_data) + 1, cbc_data);
    printf("\ndata[%d]  = ", (int)strlen(cbc_data) + 1);
    for (j = 0; j < strlen(cbc_data) + 1; j++)
        printf("%02X", cbc_data[j]);
    printf("\n");
    printf("cbc cipher text\n");
    printf("cipher[%d]= ", 32);
    for (j = 0; j < 32; j++)
        printf("%02X", cbc_ok[j]);
    printf("\n");

    printf("cfb64 cipher text\n");
    printf("cipher[%d]= ", (int)strlen(cbc_data) + 1);
    for (j = 0; j < strlen(cbc_data) + 1; j++)
        printf("%02X", cfb64_ok[j]);
    printf("\n");

    printf("ofb64 cipher text\n");
    printf("cipher[%d]= ", (int)strlen(cbc_data) + 1);
    for (j = 0; j < strlen(cbc_data) + 1; j++)
        printf("%02X", ofb64_ok[j]);
    printf("\n");
    return 0;
}