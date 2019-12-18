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
 scalar_t__ DEBUG_LEVEL ; 
 int /*<<< orphan*/  dprintf1 (char*,int) ; 
 int get_test_read_fd () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pkey_assert (int) ; 
 int /*<<< orphan*/  pkey_write_deny (int /*<<< orphan*/ ) ; 
 int read (int,int*,int) ; 

void test_kernel_write_of_write_disabled_region(int *ptr, u16 pkey)
{
	int ret;
	int test_fd = get_test_read_fd();

	pkey_write_deny(pkey);
	ret = read(test_fd, ptr, 100);
	dprintf1("read ret: %d\n", ret);
	if (ret < 0 && (DEBUG_LEVEL > 0))
		perror("verbose read result (OK for this to be bad)");
	pkey_assert(ret);
}