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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 scalar_t__ hugetlbfs_test ; 
 char* malloc (int) ; 
 int mfd_def_size ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int pwrite (int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mfd_fail_grow_write(int fd)
{
	static char *buf;
	ssize_t l;

	/* hugetlbfs does not support write */
	if (hugetlbfs_test)
		return;

	buf = malloc(mfd_def_size * 8);
	if (!buf) {
		printf("malloc(%zu) failed: %m\n", mfd_def_size * 8);
		abort();
	}

	l = pwrite(fd, buf, mfd_def_size * 8, 0);
	if (l == (mfd_def_size * 8)) {
		printf("pwrite() didn't fail as expected\n");
		abort();
	}
}