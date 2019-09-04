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
 scalar_t__ DEBUG_LEVEL ; 
 int /*<<< orphan*/  FUTEX_WAIT ; 
 int /*<<< orphan*/  SYS_futex ; 
 int /*<<< orphan*/  dprintf1 (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pkey_write_deny (int) ; 
 int syscall (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int) ; 

void test_kernel_gup_write_to_write_disabled_region(int *ptr, u16 pkey)
{
	int ignored = 0xdada;
	int futex_ret;
	int some_int = __LINE__;

	dprintf1("disabling write to PKEY[%02d], "
		 "doing futex gunk in buffer\n", pkey);
	*ptr = some_int;
	pkey_write_deny(pkey);
	futex_ret = syscall(SYS_futex, ptr, FUTEX_WAIT, some_int-1, NULL,
			&ignored, ignored);
	if (DEBUG_LEVEL > 0)
		perror("futex");
	dprintf1("futex() ret: %d\n", futex_ret);
}