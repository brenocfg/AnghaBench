#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kernfs_node {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; struct kernfs_node* i_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct TYPE_4__ {void* ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  kernfs_active (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_find_ns (struct kernfs_node*,int /*<<< orphan*/ ,void const*) ; 
 struct inode* kernfs_get_inode (int /*<<< orphan*/ ,struct kernfs_node*) ; 
 TYPE_2__* kernfs_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 scalar_t__ kernfs_ns_enabled (struct kernfs_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dentry *kernfs_iop_lookup(struct inode *dir,
					struct dentry *dentry,
					unsigned int flags)
{
	struct dentry *ret;
	struct kernfs_node *parent = dir->i_private;
	struct kernfs_node *kn;
	struct inode *inode;
	const void *ns = NULL;

	mutex_lock(&kernfs_mutex);

	if (kernfs_ns_enabled(parent))
		ns = kernfs_info(dir->i_sb)->ns;

	kn = kernfs_find_ns(parent, dentry->d_name.name, ns);

	/* no such entry */
	if (!kn || !kernfs_active(kn)) {
		ret = NULL;
		goto out_unlock;
	}

	/* attach dentry and inode */
	inode = kernfs_get_inode(dir->i_sb, kn);
	if (!inode) {
		ret = ERR_PTR(-ENOMEM);
		goto out_unlock;
	}

	/* instantiate and hash dentry */
	ret = d_splice_alias(inode, dentry);
 out_unlock:
	mutex_unlock(&kernfs_mutex);
	return ret;
}