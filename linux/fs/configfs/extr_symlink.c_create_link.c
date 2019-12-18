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
struct dentry {int dummy; } ;
struct configfs_dirent {int s_type; int /*<<< orphan*/  s_links; } ;
struct config_item {TYPE_1__* ci_dentry; } ;
struct TYPE_2__ {struct configfs_dirent* d_fsdata; } ;

/* Variables and functions */
 int CONFIGFS_USET_DROPPING ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int configfs_create_link (struct configfs_dirent*,TYPE_1__*,struct dentry*,char*) ; 
 int /*<<< orphan*/  configfs_dirent_is_ready (struct configfs_dirent*) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  configfs_get (struct configfs_dirent*) ; 
 int configfs_get_target_path (struct config_item*,struct config_item*,char*) ; 
 int /*<<< orphan*/  configfs_put (struct configfs_dirent*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_link(struct config_item *parent_item,
		       struct config_item *item,
		       struct dentry *dentry)
{
	struct configfs_dirent *target_sd = item->ci_dentry->d_fsdata;
	char *body;
	int ret;

	if (!configfs_dirent_is_ready(target_sd))
		return -ENOENT;

	body = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!body)
		return -ENOMEM;

	configfs_get(target_sd);
	spin_lock(&configfs_dirent_lock);
	if (target_sd->s_type & CONFIGFS_USET_DROPPING) {
		spin_unlock(&configfs_dirent_lock);
		configfs_put(target_sd);
		kfree(body);
		return -ENOENT;
	}
	target_sd->s_links++;
	spin_unlock(&configfs_dirent_lock);
	ret = configfs_get_target_path(parent_item, item, body);
	if (!ret)
		ret = configfs_create_link(target_sd, parent_item->ci_dentry,
					   dentry, body);
	if (ret) {
		spin_lock(&configfs_dirent_lock);
		target_sd->s_links--;
		spin_unlock(&configfs_dirent_lock);
		configfs_put(target_sd);
		kfree(body);
	}
	return ret;
}