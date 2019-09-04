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
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct core_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disconnect_channels ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_1__ mc ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int most_deregister_component(struct core_component *comp)
{
	if (!comp) {
		pr_err("Bad component\n");
		return -EINVAL;
	}

	bus_for_each_dev(&mc.bus, NULL, comp, disconnect_channels);
	list_del(&comp->list);
	pr_info("deregistering component %s\n", comp->name);
	return 0;
}