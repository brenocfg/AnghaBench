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
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int ftruncate (int,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sys_memfd_create (char const*,unsigned int) ; 

__attribute__((used)) static int mfd_assert_new(const char *name, loff_t sz, unsigned int flags)
{
	int r, fd;

	fd = sys_memfd_create(name, flags);
	if (fd < 0) {
		printf("memfd_create(\"%s\", %u) failed: %m\n",
		       name, flags);
		abort();
	}

	r = ftruncate(fd, sz);
	if (r < 0) {
		printf("ftruncate(%llu) failed: %m\n", (unsigned long long)sz);
		abort();
	}

	return fd;
}