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
 int EACCES ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int MAY_EXEC ; 
 int MAY_READ ; 
 int MAY_WRITE ; 
 int /*<<< orphan*/  current_euid () ; 
 scalar_t__ in_egroup_p (int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_perm(int mode, int op)
{
	if (uid_eq(current_euid(), GLOBAL_ROOT_UID))
		mode >>= 6;
	else if (in_egroup_p(GLOBAL_ROOT_GID))
		mode >>= 3;
	if ((op & ~mode & (MAY_READ|MAY_WRITE|MAY_EXEC)) == 0)
		return 0;
	return -EACCES;
}