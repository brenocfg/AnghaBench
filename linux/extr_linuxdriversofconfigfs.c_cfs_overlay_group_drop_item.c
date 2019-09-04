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
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;
struct cfs_overlay_item {int /*<<< orphan*/  item; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_item_put (int /*<<< orphan*/ *) ; 
 struct cfs_overlay_item* to_cfs_overlay_item (struct config_item*) ; 

__attribute__((used)) static void cfs_overlay_group_drop_item(struct config_group *group,
		struct config_item *item)
{
	struct cfs_overlay_item *overlay = to_cfs_overlay_item(item);

	config_item_put(&overlay->item);
}