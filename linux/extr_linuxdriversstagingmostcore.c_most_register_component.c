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
struct core_component {int /*<<< orphan*/  name; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  comp_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ mc ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int most_register_component(struct core_component *comp)
{
	if (!comp) {
		pr_err("Bad component\n");
		return -EINVAL;
	}
	list_add_tail(&comp->list, &mc.comp_list);
	pr_info("registered new core component %s\n", comp->name);
	return 0;
}