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
struct dlm_space {int /*<<< orphan*/  group; } ;
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 struct dlm_space* config_item_to_space (struct config_item*) ; 
 int /*<<< orphan*/  configfs_remove_default_groups (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drop_space(struct config_group *g, struct config_item *i)
{
	struct dlm_space *sp = config_item_to_space(i);

	/* assert list_empty(&sp->members) */

	configfs_remove_default_groups(&sp->group);
	config_item_put(i);
}