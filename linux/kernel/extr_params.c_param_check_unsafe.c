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
struct kernel_param {int flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int KERNEL_PARAM_FL_HWPARAM ; 
 int KERNEL_PARAM_FL_UNSAFE ; 
 int /*<<< orphan*/  LOCKDEP_STILL_OK ; 
 int /*<<< orphan*/  LOCKDOWN_MODULE_PARAMETERS ; 
 int /*<<< orphan*/  TAINT_USER ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ security_locked_down (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool param_check_unsafe(const struct kernel_param *kp)
{
	if (kp->flags & KERNEL_PARAM_FL_HWPARAM &&
	    security_locked_down(LOCKDOWN_MODULE_PARAMETERS))
		return false;

	if (kp->flags & KERNEL_PARAM_FL_UNSAFE) {
		pr_notice("Setting dangerous option %s - tainting kernel\n",
			  kp->name);
		add_taint(TAINT_USER, LOCKDEP_STILL_OK);
	}

	return true;
}