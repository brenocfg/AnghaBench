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
struct config_item {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cs_subsys; } ;

/* Variables and functions */
 int configfs_depend_item (int /*<<< orphan*/ *,struct config_item*) ; 
 TYPE_1__ o2nm_cluster_group ; 

int o2nm_depend_item(struct config_item *item)
{
	return configfs_depend_item(&o2nm_cluster_group.cs_subsys, item);
}