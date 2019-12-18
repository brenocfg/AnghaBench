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
struct dlm_space {int /*<<< orphan*/  members_lock; int /*<<< orphan*/  members_count; } ;
struct dlm_node {int /*<<< orphan*/  list; } ;
struct config_item {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ci_parent; } ;
struct config_group {TYPE_1__ cg_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 struct dlm_node* config_item_to_node (struct config_item*) ; 
 struct dlm_space* config_item_to_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drop_node(struct config_group *g, struct config_item *i)
{
	struct dlm_space *sp = config_item_to_space(g->cg_item.ci_parent);
	struct dlm_node *nd = config_item_to_node(i);

	mutex_lock(&sp->members_lock);
	list_del(&nd->list);
	sp->members_count--;
	mutex_unlock(&sp->members_lock);

	config_item_put(i);
}