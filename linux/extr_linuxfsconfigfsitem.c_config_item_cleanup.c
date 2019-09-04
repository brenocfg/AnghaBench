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
struct config_item_type {TYPE_1__* ct_item_ops; } ;
struct config_item {int /*<<< orphan*/ * ci_name; int /*<<< orphan*/ * ci_namebuf; struct config_item* ci_parent; struct config_group* ci_group; struct config_item_type* ci_type; } ;
struct config_group {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* release ) (struct config_item*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  config_group_put (struct config_group*) ; 
 int /*<<< orphan*/  config_item_name (struct config_item*) ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct config_item*) ; 

__attribute__((used)) static void config_item_cleanup(struct config_item *item)
{
	const struct config_item_type *t = item->ci_type;
	struct config_group *s = item->ci_group;
	struct config_item *parent = item->ci_parent;

	pr_debug("config_item %s: cleaning up\n", config_item_name(item));
	if (item->ci_name != item->ci_namebuf)
		kfree(item->ci_name);
	item->ci_name = NULL;
	if (t && t->ct_item_ops && t->ct_item_ops->release)
		t->ct_item_ops->release(item);
	if (s)
		config_group_put(s);
	if (parent)
		config_item_put(parent);
}