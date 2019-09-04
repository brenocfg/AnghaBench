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
struct qstr {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct fuse_entry_out {int dummy; } ;
struct fuse_conn {int /*<<< orphan*/  export_support; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 int ESTALE ; 
 scalar_t__ FUSE_ROOT_ID ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 struct qstr QSTR_INIT (char*,int) ; 
 struct inode* d_inode (struct dentry*) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 int /*<<< orphan*/  fuse_invalidate_entry_cache (struct dentry*) ; 
 int fuse_lookup_name (int /*<<< orphan*/ ,scalar_t__,struct qstr const*,struct fuse_entry_out*,struct inode**) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 scalar_t__ get_node_id (struct inode*) ; 

__attribute__((used)) static struct dentry *fuse_get_parent(struct dentry *child)
{
	struct inode *child_inode = d_inode(child);
	struct fuse_conn *fc = get_fuse_conn(child_inode);
	struct inode *inode;
	struct dentry *parent;
	struct fuse_entry_out outarg;
	const struct qstr name = QSTR_INIT("..", 2);
	int err;

	if (!fc->export_support)
		return ERR_PTR(-ESTALE);

	err = fuse_lookup_name(child_inode->i_sb, get_node_id(child_inode),
			       &name, &outarg, &inode);
	if (err) {
		if (err == -ENOENT)
			return ERR_PTR(-ESTALE);
		return ERR_PTR(err);
	}

	parent = d_obtain_alias(inode);
	if (!IS_ERR(parent) && get_node_id(inode) != FUSE_ROOT_ID)
		fuse_invalidate_entry_cache(parent);

	return parent;
}