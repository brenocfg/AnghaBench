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
struct dev_exception_item {int /*<<< orphan*/  access; int /*<<< orphan*/  minor; int /*<<< orphan*/  major; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct dev_cgroup {scalar_t__ behavior; int /*<<< orphan*/  exceptions; TYPE_1__ css; } ;

/* Variables and functions */
 scalar_t__ DEVCG_DEFAULT_DENY ; 
 struct dev_cgroup* css_to_devcgroup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_exception_partial (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool parent_allows_removal(struct dev_cgroup *childcg,
				  struct dev_exception_item *ex)
{
	struct dev_cgroup *parent = css_to_devcgroup(childcg->css.parent);

	if (!parent)
		return true;

	/* It's always allowed to remove access to devices */
	if (childcg->behavior == DEVCG_DEFAULT_DENY)
		return true;

	/*
	 * Make sure you're not removing part or a whole exception existing in
	 * the parent cgroup
	 */
	return !match_exception_partial(&parent->exceptions, ex->type,
					ex->major, ex->minor, ex->access);
}