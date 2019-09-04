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
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_parent; int /*<<< orphan*/  d_wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 struct dentry* d_alloc (int /*<<< orphan*/ ,struct qstr*) ; 
 struct dentry* d_alloc_parallel (int /*<<< orphan*/ ,struct qstr*,int /*<<< orphan*/ ) ; 
 struct dentry* d_hash_and_lookup (int /*<<< orphan*/ ,struct qstr*) ; 
 scalar_t__ d_in_lookup (struct dentry*) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

struct dentry *d_add_ci(struct dentry *dentry, struct inode *inode,
			struct qstr *name)
{
	struct dentry *found, *res;

	/*
	 * First check if a dentry matching the name already exists,
	 * if not go ahead and create it now.
	 */
	found = d_hash_and_lookup(dentry->d_parent, name);
	if (found) {
		iput(inode);
		return found;
	}
	if (d_in_lookup(dentry)) {
		found = d_alloc_parallel(dentry->d_parent, name,
					dentry->d_wait);
		if (IS_ERR(found) || !d_in_lookup(found)) {
			iput(inode);
			return found;
		}
	} else {
		found = d_alloc(dentry->d_parent, name);
		if (!found) {
			iput(inode);
			return ERR_PTR(-ENOMEM);
		} 
	}
	res = d_splice_alias(inode, found);
	if (res) {
		dput(found);
		return res;
	}
	return found;
}