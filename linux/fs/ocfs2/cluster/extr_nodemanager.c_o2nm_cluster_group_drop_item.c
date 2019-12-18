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
struct o2nm_cluster {int /*<<< orphan*/  cl_group; } ;
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  configfs_remove_default_groups (int /*<<< orphan*/ *) ; 
 struct o2nm_cluster* o2nm_single_cluster ; 
 struct o2nm_cluster* to_o2nm_cluster (struct config_item*) ; 

__attribute__((used)) static void o2nm_cluster_group_drop_item(struct config_group *group, struct config_item *item)
{
	struct o2nm_cluster *cluster = to_o2nm_cluster(item);

	BUG_ON(o2nm_single_cluster != cluster);
	o2nm_single_cluster = NULL;

	configfs_remove_default_groups(&cluster->cl_group);
	config_item_put(item);
}