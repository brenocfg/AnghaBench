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
 int /*<<< orphan*/  BF_ENCRYPT ; 
 int /*<<< orphan*/  BF_ecb_encrypt (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BF_set_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  key_data ; 
 int /*<<< orphan*/ ** key_out ; 
 int /*<<< orphan*/  key_test ; 

__attribute__((used)) static int test_bf_set_key(int n)
{
    int ret = 1;
    BF_KEY key;
    unsigned char out[8];

    BF_set_key(&key, n+1, key_test);
    BF_ecb_encrypt(key_data, out, &key, BF_ENCRYPT);
    /* mips-sgi-irix6.5-gcc  vv  -mabi=64 bug workaround */
    if (!TEST_mem_eq(out, 8, &(key_out[n][0]), 8))
        ret = 0;

    return ret;
}