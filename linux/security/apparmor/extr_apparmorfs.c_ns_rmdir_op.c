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
struct inode {int /*<<< orphan*/  i_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {struct inode* d_inode; TYPE_1__ d_name; } ;
struct aa_ns {int /*<<< orphan*/  lock; int /*<<< orphan*/  sub_ns; int /*<<< orphan*/  level; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_MAY_LOAD_POLICY ; 
 int ENOENT ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  __aa_findn_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __aa_remove_ns (struct aa_ns*) ; 
 struct aa_ns* aa_get_ns (int /*<<< orphan*/ ) ; 
 int aa_may_manage_policy (struct aa_label*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_ns (struct aa_ns*) ; 
 struct aa_label* begin_current_label_crit_section () ; 
 int /*<<< orphan*/  end_current_label_crit_section (struct aa_label*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dentry* ns_dir (struct aa_ns*) ; 

__attribute__((used)) static int ns_rmdir_op(struct inode *dir, struct dentry *dentry)
{
	struct aa_ns *ns, *parent;
	/* TODO: improve permission check */
	struct aa_label *label;
	int error;

	label = begin_current_label_crit_section();
	error = aa_may_manage_policy(label, NULL, AA_MAY_LOAD_POLICY);
	end_current_label_crit_section(label);
	if (error)
		return error;

	parent = aa_get_ns(dir->i_private);
	/* rmdir calls the generic securityfs functions to remove files
	 * from the apparmor dir. It is up to the apparmor ns locking
	 * to avoid races.
	 */
	inode_unlock(dir);
	inode_unlock(dentry->d_inode);

	mutex_lock_nested(&parent->lock, parent->level);
	ns = aa_get_ns(__aa_findn_ns(&parent->sub_ns, dentry->d_name.name,
				     dentry->d_name.len));
	if (!ns) {
		error = -ENOENT;
		goto out;
	}
	AA_BUG(ns_dir(ns) != dentry);

	__aa_remove_ns(ns);
	aa_put_ns(ns);

out:
	mutex_unlock(&parent->lock);
	inode_lock_nested(dir, I_MUTEX_PARENT);
	inode_lock(dentry->d_inode);
	aa_put_ns(parent);

	return error;
}