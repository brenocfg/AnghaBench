#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_3__* i_sb; int /*<<< orphan*/  i_lock; int /*<<< orphan*/  i_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/  d_parent; TYPE_1__ d_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_id; TYPE_2__* s_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ELOOP ; 
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  IS_ROOT (struct dentry*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __d_add (struct dentry*,struct inode*) ; 
 struct dentry* __d_find_any_alias (struct inode*) ; 
 int /*<<< orphan*/  __d_move (struct dentry*,struct dentry*,int) ; 
 int __d_unalias (struct inode*,struct dentry*,struct dentry*) ; 
 struct dentry* d_ancestor (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rename_lock ; 
 int /*<<< orphan*/  security_d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (struct dentry*) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

struct dentry *d_splice_alias(struct inode *inode, struct dentry *dentry)
{
	if (IS_ERR(inode))
		return ERR_CAST(inode);

	BUG_ON(!d_unhashed(dentry));

	if (!inode)
		goto out;

	security_d_instantiate(dentry, inode);
	spin_lock(&inode->i_lock);
	if (S_ISDIR(inode->i_mode)) {
		struct dentry *new = __d_find_any_alias(inode);
		if (unlikely(new)) {
			/* The reference to new ensures it remains an alias */
			spin_unlock(&inode->i_lock);
			write_seqlock(&rename_lock);
			if (unlikely(d_ancestor(new, dentry))) {
				write_sequnlock(&rename_lock);
				dput(new);
				new = ERR_PTR(-ELOOP);
				pr_warn_ratelimited(
					"VFS: Lookup of '%s' in %s %s"
					" would have caused loop\n",
					dentry->d_name.name,
					inode->i_sb->s_type->name,
					inode->i_sb->s_id);
			} else if (!IS_ROOT(new)) {
				struct dentry *old_parent = dget(new->d_parent);
				int err = __d_unalias(inode, dentry, new);
				write_sequnlock(&rename_lock);
				if (err) {
					dput(new);
					new = ERR_PTR(err);
				}
				dput(old_parent);
			} else {
				__d_move(new, dentry, false);
				write_sequnlock(&rename_lock);
			}
			iput(inode);
			return new;
		}
	}
out:
	__d_add(dentry, inode);
	return NULL;
}