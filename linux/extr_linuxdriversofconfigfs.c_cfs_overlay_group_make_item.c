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
struct cfs_overlay_item {struct config_item item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_item* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfs_overlay_type ; 
 int /*<<< orphan*/  config_item_init_type_name (struct config_item*,char const*,int /*<<< orphan*/ *) ; 
 struct cfs_overlay_item* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct config_item *cfs_overlay_group_make_item(
		struct config_group *group, const char *name)
{
	struct cfs_overlay_item *overlay;

	overlay = kzalloc(sizeof(*overlay), GFP_KERNEL);
	if (!overlay)
		return ERR_PTR(-ENOMEM);

	config_item_init_type_name(&overlay->item, name, &cfs_overlay_type);
	return &overlay->item;
}