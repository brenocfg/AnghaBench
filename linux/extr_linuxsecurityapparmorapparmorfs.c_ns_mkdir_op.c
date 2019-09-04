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
typedef  int umode_t ;
struct inode {int /*<<< orphan*/  i_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct aa_ns {int /*<<< orphan*/  lock; int /*<<< orphan*/  level; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int) ; 
 int /*<<< orphan*/  AA_MAY_LOAD_POLICY ; 
 scalar_t__ IS_ERR (struct aa_ns*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int PTR_ERR (struct aa_ns*) ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int S_IFDIR ; 
 struct aa_ns* __aa_find_or_create_ns (struct aa_ns*,int /*<<< orphan*/ ,struct dentry*) ; 
 int __aafs_setup_d_inode (struct inode*,struct dentry*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct aa_ns* aa_get_ns (int /*<<< orphan*/ ) ; 
 int aa_may_manage_policy (struct aa_label*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_ns (struct aa_ns*) ; 
 int /*<<< orphan*/  aafs_count ; 
 int /*<<< orphan*/  aafs_mnt ; 
 int /*<<< orphan*/  aafs_ops ; 
 struct aa_label* begin_current_label_crit_section () ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_current_label_crit_section (struct aa_label*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_subns_dir (struct aa_ns*) ; 
 int simple_pin_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_release_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ns_mkdir_op(struct inode *dir, struct dentry *dentry, umode_t mode)
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
	AA_BUG(d_inode(ns_subns_dir(parent)) != dir);

	/* we have to unlock and then relock to get locking order right
	 * for pin_fs
	 */
	inode_unlock(dir);
	error = simple_pin_fs(&aafs_ops, &aafs_mnt, &aafs_count);
	mutex_lock_nested(&parent->lock, parent->level);
	inode_lock_nested(dir, I_MUTEX_PARENT);
	if (error)
		goto out;

	error = __aafs_setup_d_inode(dir, dentry, mode | S_IFDIR,  NULL,
				     NULL, NULL, NULL);
	if (error)
		goto out_pin;

	ns = __aa_find_or_create_ns(parent, READ_ONCE(dentry->d_name.name),
				    dentry);
	if (IS_ERR(ns)) {
		error = PTR_ERR(ns);
		ns = NULL;
	}

	aa_put_ns(ns);		/* list ref remains */
out_pin:
	if (error)
		simple_release_fs(&aafs_mnt, &aafs_count);
out:
	mutex_unlock(&parent->lock);
	aa_put_ns(parent);

	return error;
}