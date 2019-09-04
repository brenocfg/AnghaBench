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
struct dlm_cluster {int /*<<< orphan*/  group; } ;
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * comm_list ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 struct dlm_cluster* config_item_to_cluster (struct config_item*) ; 
 int /*<<< orphan*/  configfs_remove_default_groups (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * space_list ; 

__attribute__((used)) static void drop_cluster(struct config_group *g, struct config_item *i)
{
	struct dlm_cluster *cl = config_item_to_cluster(i);

	configfs_remove_default_groups(&cl->group);

	space_list = NULL;
	comm_list = NULL;

	config_item_put(i);
}