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
struct dev_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dev_exception_clean (struct dev_cgroup*) ; 
 int /*<<< orphan*/  devcgroup_mutex ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dev_exception_clean(struct dev_cgroup *dev_cgroup)
{
	lockdep_assert_held(&devcgroup_mutex);

	__dev_exception_clean(dev_cgroup);
}