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
struct config_item_type {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct config_group* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,struct config_item_type const*) ; 
 int configfs_register_group (struct config_group*,struct config_group*) ; 
 int /*<<< orphan*/  kfree (struct config_group*) ; 
 struct config_group* kzalloc (int,int /*<<< orphan*/ ) ; 

struct config_group *
configfs_register_default_group(struct config_group *parent_group,
				const char *name,
				const struct config_item_type *item_type)
{
	int ret;
	struct config_group *group;

	group = kzalloc(sizeof(*group), GFP_KERNEL);
	if (!group)
		return ERR_PTR(-ENOMEM);
	config_group_init_type_name(group, name, item_type);

	ret = configfs_register_group(parent_group, group);
	if (ret) {
		kfree(group);
		return ERR_PTR(ret);
	}
	return group;
}