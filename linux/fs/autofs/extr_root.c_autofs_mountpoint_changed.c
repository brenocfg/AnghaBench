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
struct path {struct dentry* dentry; } ;
struct dentry {int /*<<< orphan*/  d_name; struct dentry* d_parent; int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int /*<<< orphan*/  type; } ;
struct autofs_info {int /*<<< orphan*/  last_used; } ;

/* Variables and functions */
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 scalar_t__ autofs_type_indirect (int /*<<< orphan*/ ) ; 
 struct dentry* d_lookup (struct dentry*,int /*<<< orphan*/ *) ; 
 scalar_t__ d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static struct dentry *autofs_mountpoint_changed(struct path *path)
{
	struct dentry *dentry = path->dentry;
	struct autofs_sb_info *sbi = autofs_sbi(dentry->d_sb);

	/*
	 * If this is an indirect mount the dentry could have gone away
	 * as a result of an expire and a new one created.
	 */
	if (autofs_type_indirect(sbi->type) && d_unhashed(dentry)) {
		struct dentry *parent = dentry->d_parent;
		struct autofs_info *ino;
		struct dentry *new;

		new = d_lookup(parent, &dentry->d_name);
		if (!new)
			return NULL;
		ino = autofs_dentry_ino(new);
		ino->last_used = jiffies;
		dput(path->dentry);
		path->dentry = new;
	}
	return path->dentry;
}