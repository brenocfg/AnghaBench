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

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int sys_statx (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void test_lookup_fail(int fd, const char *pathname)
{
	char stx[256] __attribute__((aligned(8)));
	int rv;

	rv = sys_statx(fd, pathname, AT_SYMLINK_NOFOLLOW, 0, (void *)stx);
	assert(rv == -1 && errno == ENOENT);
}