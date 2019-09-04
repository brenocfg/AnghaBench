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
struct dev_exception_item {int /*<<< orphan*/  access; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  type; } ;
struct dev_cgroup {scalar_t__ behavior; int /*<<< orphan*/  exceptions; } ;
typedef  enum devcg_behavior { ____Placeholder_devcg_behavior } devcg_behavior ;

/* Variables and functions */
 scalar_t__ DEVCG_DEFAULT_ALLOW ; 
 int /*<<< orphan*/  RCU_LOCKDEP_WARN (int,char*) ; 
 int /*<<< orphan*/  devcgroup_mutex ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int match_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int match_exception_partial (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 

__attribute__((used)) static bool verify_new_ex(struct dev_cgroup *dev_cgroup,
		          struct dev_exception_item *refex,
		          enum devcg_behavior behavior)
{
	bool match = false;

	RCU_LOCKDEP_WARN(!rcu_read_lock_held() &&
			 !lockdep_is_held(&devcgroup_mutex),
			 "device_cgroup:verify_new_ex called without proper synchronization");

	if (dev_cgroup->behavior == DEVCG_DEFAULT_ALLOW) {
		if (behavior == DEVCG_DEFAULT_ALLOW) {
			/*
			 * new exception in the child doesn't matter, only
			 * adding extra restrictions
			 */ 
			return true;
		} else {
			/*
			 * new exception in the child will add more devices
			 * that can be acessed, so it can't match any of
			 * parent's exceptions, even slightly
			 */ 
			match = match_exception_partial(&dev_cgroup->exceptions,
							refex->type,
							refex->major,
							refex->minor,
							refex->access);

			if (match)
				return false;
			return true;
		}
	} else {
		/*
		 * Only behavior == DEVCG_DEFAULT_DENY allowed here, therefore
		 * the new exception will add access to more devices and must
		 * be contained completely in an parent's exception to be
		 * allowed
		 */
		match = match_exception(&dev_cgroup->exceptions, refex->type,
					refex->major, refex->minor,
					refex->access);

		if (match)
			/* parent has an exception that matches the proposed */
			return true;
		else
			return false;
	}
	return false;
}