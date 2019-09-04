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
typedef  int u16 ;

/* Variables and functions */
 int NR_PKEYS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  dprintf1 (char*,int) ; 
 int /*<<< orphan*/  pkey_assert (int) ; 
 int sys_mprotect_pkey (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sys_pkey_free (int) ; 

void test_pkey_syscalls_on_non_allocated_pkey(int *ptr, u16 pkey)
{
	int err;
	int i;

	/* Note: 0 is the default pkey, so don't mess with it */
	for (i = 1; i < NR_PKEYS; i++) {
		if (pkey == i)
			continue;

		dprintf1("trying get/set/free to non-allocated pkey: %2d\n", i);
		err = sys_pkey_free(i);
		pkey_assert(err);

		err = sys_pkey_free(i);
		pkey_assert(err);

		err = sys_mprotect_pkey(ptr, PAGE_SIZE, PROT_READ, i);
		pkey_assert(err);
	}
}