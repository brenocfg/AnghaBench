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
struct config_group {int /*<<< orphan*/  default_groups; int /*<<< orphan*/  cg_children; int /*<<< orphan*/  cg_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_item_init (int /*<<< orphan*/ *) ; 

void config_group_init(struct config_group *group)
{
	config_item_init(&group->cg_item);
	INIT_LIST_HEAD(&group->cg_children);
	INIT_LIST_HEAD(&group->default_groups);
}