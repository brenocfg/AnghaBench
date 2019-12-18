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
struct ovl_layer {int /*<<< orphan*/  idx; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct name_snapshot {TYPE_1__ name; } ;
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int ECHILD ; 
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 int ESTALE ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int PTR_ERR (struct dentry*) ; 
 struct inode* d_inode (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 struct dentry* ovl_dentry_real_at (struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,struct dentry*,int /*<<< orphan*/ ,struct dentry*,int) ; 
 int /*<<< orphan*/  release_dentry_name_snapshot (struct name_snapshot*) ; 
 int /*<<< orphan*/  take_dentry_name_snapshot (struct name_snapshot*,struct dentry*) ; 

__attribute__((used)) static struct dentry *ovl_lookup_real_one(struct dentry *connected,
					  struct dentry *real,
					  struct ovl_layer *layer)
{
	struct inode *dir = d_inode(connected);
	struct dentry *this, *parent = NULL;
	struct name_snapshot name;
	int err;

	/*
	 * Lookup child overlay dentry by real name. The dir mutex protects us
	 * from racing with overlay rename. If the overlay dentry that is above
	 * real has already been moved to a parent that is not under the
	 * connected overlay dir, we return -ECHILD and restart the lookup of
	 * connected real path from the top.
	 */
	inode_lock_nested(dir, I_MUTEX_PARENT);
	err = -ECHILD;
	parent = dget_parent(real);
	if (ovl_dentry_real_at(connected, layer->idx) != parent)
		goto fail;

	/*
	 * We also need to take a snapshot of real dentry name to protect us
	 * from racing with underlying layer rename. In this case, we don't
	 * care about returning ESTALE, only from dereferencing a free name
	 * pointer because we hold no lock on the real dentry.
	 */
	take_dentry_name_snapshot(&name, real);
	this = lookup_one_len(name.name.name, connected, name.name.len);
	err = PTR_ERR(this);
	if (IS_ERR(this)) {
		goto fail;
	} else if (!this || !this->d_inode) {
		dput(this);
		err = -ENOENT;
		goto fail;
	} else if (ovl_dentry_real_at(this, layer->idx) != real) {
		dput(this);
		err = -ESTALE;
		goto fail;
	}

out:
	release_dentry_name_snapshot(&name);
	dput(parent);
	inode_unlock(dir);
	return this;

fail:
	pr_warn_ratelimited("overlayfs: failed to lookup one by real (%pd2, layer=%d, connected=%pd2, err=%i)\n",
			    real, layer->idx, connected, err);
	this = ERR_PTR(err);
	goto out;
}