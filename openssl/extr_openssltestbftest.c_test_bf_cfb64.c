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
typedef  int BF_LONG ;
typedef  int /*<<< orphan*/  BF_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  BF_DECRYPT ; 
 int /*<<< orphan*/  BF_ENCRYPT ; 
 int /*<<< orphan*/  BF_cfb64_encrypt (unsigned char*,unsigned char*,int,int /*<<< orphan*/ *,unsigned char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BF_set_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * cbc_data ; 
 int /*<<< orphan*/  cbc_iv ; 
 int /*<<< orphan*/  cbc_key ; 
 int /*<<< orphan*/ * cfb64_ok ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_bf_cfb64(void)
{
    unsigned char cbc_in[40], cbc_out[40], iv[8];
    int n, ret = 1;
    BF_KEY key;
    BF_LONG len;

    len = strlen(cbc_data) + 1;

    BF_set_key(&key, 16, cbc_key);
    memset(cbc_in, 0, 40);
    memset(cbc_out, 0, 40);
    memcpy(iv, cbc_iv, 8);
    n = 0;
    BF_cfb64_encrypt((unsigned char *)cbc_data, cbc_out, (long)13,
                     &key, iv, &n, BF_ENCRYPT);
    BF_cfb64_encrypt((unsigned char *)&(cbc_data[13]), &(cbc_out[13]),
                     len - 13, &key, iv, &n, BF_ENCRYPT);
    if (!TEST_mem_eq(cbc_out, (int)len, cfb64_ok, (int)len))
        ret = 0;

    n = 0;
    memcpy(iv, cbc_iv, 8);
    BF_cfb64_encrypt(cbc_out, cbc_in, 17, &key, iv, &n, BF_DECRYPT);
    BF_cfb64_encrypt(&(cbc_out[17]), &(cbc_in[17]), len - 17,
                     &key, iv, &n, BF_DECRYPT);
    if (!TEST_mem_eq(cbc_in, (int)len, cbc_data, (int)len))
        ret = 0;

    return ret;
}