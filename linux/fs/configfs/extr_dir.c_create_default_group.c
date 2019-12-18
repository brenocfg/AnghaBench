#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dentry {struct configfs_dirent* d_fsdata; } ;
struct configfs_fragment {int dummy; } ;
struct configfs_dirent {int /*<<< orphan*/  s_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  ci_name; int /*<<< orphan*/  ci_namebuf; struct dentry* ci_dentry; } ;
struct config_group {TYPE_1__ cg_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONFIGFS_USET_DEFAULT ; 
 int ENOMEM ; 
 int configfs_attach_group (TYPE_1__*,TYPE_1__*,struct dentry*,struct configfs_fragment*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_alloc_name (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 

__attribute__((used)) static int create_default_group(struct config_group *parent_group,
				struct config_group *group,
				struct configfs_fragment *frag)
{
	int ret;
	struct configfs_dirent *sd;
	/* We trust the caller holds a reference to parent */
	struct dentry *child, *parent = parent_group->cg_item.ci_dentry;

	if (!group->cg_item.ci_name)
		group->cg_item.ci_name = group->cg_item.ci_namebuf;

	ret = -ENOMEM;
	child = d_alloc_name(parent, group->cg_item.ci_name);
	if (child) {
		d_add(child, NULL);

		ret = configfs_attach_group(&parent_group->cg_item,
					    &group->cg_item, child, frag);
		if (!ret) {
			sd = child->d_fsdata;
			sd->s_type |= CONFIGFS_USET_DEFAULT;
		} else {
			BUG_ON(d_inode(child));
			d_drop(child);
			dput(child);
		}
	}

	return ret;
}