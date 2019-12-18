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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_OPT_NOAUDIT ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int cred_has_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_cred () ; 

__attribute__((used)) static int selinux_vm_enough_memory(struct mm_struct *mm, long pages)
{
	int rc, cap_sys_admin = 0;

	rc = cred_has_capability(current_cred(), CAP_SYS_ADMIN,
				 CAP_OPT_NOAUDIT, true);
	if (rc == 0)
		cap_sys_admin = 1;

	return cap_sys_admin;
}