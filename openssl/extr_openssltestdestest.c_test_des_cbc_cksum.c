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
typedef  int /*<<< orphan*/  DES_LONG ;

/* Variables and functions */
 int /*<<< orphan*/  DES_cbc_cksum (scalar_t__,unsigned char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DES_set_key_checked (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_cs_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TEST_mem_eq (unsigned char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cbc_cksum_data ; 
 int /*<<< orphan*/  cbc_cksum_ret ; 
 scalar_t__ cbc_data ; 
 int /*<<< orphan*/  cbc_iv ; 
 int /*<<< orphan*/  cbc_key ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int test_des_cbc_cksum(void)
{
    DES_LONG cs;
    DES_key_schedule ks;
    unsigned char cret[8];

    DES_set_key_checked(&cbc_key, &ks);
    cs = DES_cbc_cksum(cbc_data, &cret, strlen((char *)cbc_data), &ks,
                       &cbc_iv);
    if (!TEST_cs_eq(cs, cbc_cksum_ret))
        return 0;
    return TEST_mem_eq(cret, 8, cbc_cksum_data, 8);
}