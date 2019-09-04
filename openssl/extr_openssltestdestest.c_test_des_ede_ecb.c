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
typedef  int /*<<< orphan*/  DES_key_schedule ;
typedef  int /*<<< orphan*/  DES_cblock ;

/* Variables and functions */
 int DATA_BUF_SIZE ; 
 int /*<<< orphan*/  DES_DECRYPT ; 
 int /*<<< orphan*/  DES_ENCRYPT ; 
 int /*<<< orphan*/  DES_ecb3_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DES_set_key_unchecked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_info (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * cipher_ecb2 ; 
 int /*<<< orphan*/ * key_data ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * plain_data ; 
 int /*<<< orphan*/  pt (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int test_des_ede_ecb(int i)
{
    DES_cblock in, out, outin;
    DES_key_schedule ks, ks2, ks3;
    char b1[DATA_BUF_SIZE], b2[DATA_BUF_SIZE];

    DES_set_key_unchecked(&key_data[i], &ks);
    DES_set_key_unchecked(&key_data[i + 1], &ks2);
    DES_set_key_unchecked(&key_data[i + 2], &ks3);
    memcpy(in, plain_data[i], 8);
    memset(out, 0, 8);
    memset(outin, 0, 8);
    DES_ecb3_encrypt(&in, &out, &ks, &ks2, &ks, DES_ENCRYPT);
    DES_ecb3_encrypt(&out, &outin, &ks, &ks2, &ks, DES_DECRYPT);

    if (!TEST_mem_eq(out, 8, cipher_ecb2[i], 8)) {
        TEST_info("Encryption error %2d k=%s p=%s", i + 1,
                  pt(key_data[i], b1), pt(in, b2));
        return 0;
    }
    if (!TEST_mem_eq(in, 8, outin, 8)) {
        TEST_info("Decryption error %2d k=%s p=%s ", i + 1,
                  pt(key_data[i], b1), pt(out, b2));
        return 0;
    }
    return 1;
}