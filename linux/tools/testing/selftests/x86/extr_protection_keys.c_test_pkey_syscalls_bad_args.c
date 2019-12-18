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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int NR_PKEYS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  pkey_assert (int) ; 
 int sys_mprotect_pkey (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void test_pkey_syscalls_bad_args(int *ptr, u16 pkey)
{
	int err;
	int bad_pkey = NR_PKEYS+99;

	/* pass a known-invalid pkey in: */
	err = sys_mprotect_pkey(ptr, PAGE_SIZE, PROT_READ, bad_pkey);
	pkey_assert(err);
}