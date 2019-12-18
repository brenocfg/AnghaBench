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
struct config_item {TYPE_1__* ci_group; int /*<<< orphan*/  ci_entry; struct config_item* ci_parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  cg_children; } ;

/* Variables and functions */
 TYPE_1__* config_group_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_item_get (struct config_item*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_config_group (struct config_item*) ; 

__attribute__((used)) static void link_obj(struct config_item *parent_item, struct config_item *item)
{
	/*
	 * Parent seems redundant with group, but it makes certain
	 * traversals much nicer.
	 */
	item->ci_parent = parent_item;

	/*
	 * We hold a reference on the parent for the child's ci_parent
	 * link.
	 */
	item->ci_group = config_group_get(to_config_group(parent_item));
	list_add_tail(&item->ci_entry, &item->ci_group->cg_children);

	/*
	 * We hold a reference on the child for ci_entry on the parent's
	 * cg_children
	 */
	config_item_get(item);
}