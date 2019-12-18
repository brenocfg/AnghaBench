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
 scalar_t__ ENOSYS ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,...) ; 
 int /*<<< orphan*/  stdout ; 
 long syscall (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_enosys(unsigned long nr, bool *ok)
{
	/* If this fails, a segfault is reasonably likely. */
	fflush(stdout);

	long ret = syscall(nr, 0, 0, 0, 0, 0, 0);
	if (ret == 0) {
		printf("[FAIL]\tsyscall %lu succeeded, but it should have failed\n", nr);
		*ok = false;
	} else if (errno != ENOSYS) {
		printf("[FAIL]\tsyscall %lu had error code %d, but it should have reported ENOSYS\n", nr, errno);
		*ok = false;
	}
}