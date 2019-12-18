#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dev_exception_item {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct dev_cgroup {int /*<<< orphan*/  behavior; TYPE_1__ css; } ;

/* Variables and functions */
 struct dev_cgroup* css_to_devcgroup (int /*<<< orphan*/ ) ; 
 int verify_new_ex (struct dev_cgroup*,struct dev_exception_item*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parent_has_perm(struct dev_cgroup *childcg,
				  struct dev_exception_item *ex)
{
	struct dev_cgroup *parent = css_to_devcgroup(childcg->css.parent);

	if (!parent)
		return 1;
	return verify_new_ex(parent, ex, childcg->behavior);
}