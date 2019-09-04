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
typedef  int /*<<< orphan*/  u32 ;
struct dev_cgroup {scalar_t__ behavior; int /*<<< orphan*/  exceptions; } ;

/* Variables and functions */
 scalar_t__ DEVCG_DEFAULT_ALLOW ; 
 int EPERM ; 
 int /*<<< orphan*/  current ; 
 int match_exception (int /*<<< orphan*/ *,short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  match_exception_partial (int /*<<< orphan*/ *,short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct dev_cgroup* task_devcgroup (int /*<<< orphan*/ ) ; 

int __devcgroup_check_permission(short type, u32 major, u32 minor,
				 short access)
{
	struct dev_cgroup *dev_cgroup;
	bool rc;

	rcu_read_lock();
	dev_cgroup = task_devcgroup(current);
	if (dev_cgroup->behavior == DEVCG_DEFAULT_ALLOW)
		/* Can't match any of the exceptions, even partially */
		rc = !match_exception_partial(&dev_cgroup->exceptions,
					      type, major, minor, access);
	else
		/* Need to match completely one exception to be allowed */
		rc = match_exception(&dev_cgroup->exceptions, type, major,
				     minor, access);
	rcu_read_unlock();

	if (!rc)
		return -EPERM;

	return 0;
}