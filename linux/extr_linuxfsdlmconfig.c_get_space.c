#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dlm_space {int dummy; } ;
struct config_item {int dummy; } ;
struct TYPE_5__ {TYPE_1__* cg_subsys; } ;
struct TYPE_4__ {int /*<<< orphan*/  su_mutex; } ;

/* Variables and functions */
 struct config_item* config_group_find_item (TYPE_2__*,char*) ; 
 struct dlm_space* config_item_to_space (struct config_item*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* space_list ; 

__attribute__((used)) static struct dlm_space *get_space(char *name)
{
	struct config_item *i;

	if (!space_list)
		return NULL;

	mutex_lock(&space_list->cg_subsys->su_mutex);
	i = config_group_find_item(space_list, name);
	mutex_unlock(&space_list->cg_subsys->su_mutex);

	return config_item_to_space(i);
}