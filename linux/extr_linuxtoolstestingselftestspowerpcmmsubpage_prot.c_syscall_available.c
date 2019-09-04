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
 scalar_t__ ENOENT ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  __NR_subpage_prot ; 
 scalar_t__ errno ; 
 int syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int syscall_available(void)
{
	int rc;

	errno = 0;
	rc = syscall(__NR_subpage_prot, 0, 0, 0);

	return rc == 0 || (errno != ENOENT && errno != ENOSYS);
}