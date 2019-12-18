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
struct dentry {int /*<<< orphan*/  d_lock; struct configfs_dirent* d_fsdata; } ;
struct configfs_dirent {int /*<<< orphan*/  s_element; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 struct config_item* config_item_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct config_item *configfs_get_config_item(struct dentry *dentry)
{
	struct config_item * item = NULL;

	spin_lock(&dentry->d_lock);
	if (!d_unhashed(dentry)) {
		struct configfs_dirent * sd = dentry->d_fsdata;
		item = config_item_get(sd->s_element);
	}
	spin_unlock(&dentry->d_lock);

	return item;
}