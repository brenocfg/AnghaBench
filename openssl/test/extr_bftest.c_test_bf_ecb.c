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
typedef  int /*<<< orphan*/  BF_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  BF_BLOCK ; 
 int /*<<< orphan*/  BF_DECRYPT ; 
 int /*<<< orphan*/  BF_ENCRYPT ; 
 int /*<<< orphan*/  BF_ecb_encrypt (unsigned char*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BF_set_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 unsigned char** cipher_data ; 
 int /*<<< orphan*/ * ecb_data ; 
 unsigned char** plain_data ; 

__attribute__((used)) static int test_bf_ecb(int n)
{
    int ret = 1;
    BF_KEY key;
    unsigned char out[8];

    BF_set_key(&key, 8, ecb_data[n]);

    BF_ecb_encrypt(&(plain_data[n][0]), out, &key, BF_ENCRYPT);
    if (!TEST_mem_eq(&(cipher_data[n][0]), BF_BLOCK, out, BF_BLOCK))
        ret = 0;

    BF_ecb_encrypt(out, out, &key, BF_DECRYPT);
    if (!TEST_mem_eq(&(plain_data[n][0]), BF_BLOCK, out, BF_BLOCK))
        ret = 0;

    return ret;
}