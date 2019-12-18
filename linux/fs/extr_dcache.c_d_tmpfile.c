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
struct inode {scalar_t__ i_ino; } ;
struct TYPE_5__ {scalar_t__ name; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_alias; } ;
struct dentry {scalar_t__ d_iname; TYPE_3__* d_parent; int /*<<< orphan*/  d_lock; TYPE_2__ d_name; TYPE_1__ d_u; } ;
struct TYPE_6__ {int /*<<< orphan*/  d_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DENTRY_D_LOCK_NESTED ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  d_unlinked (struct dentry*) ; 
 int /*<<< orphan*/  hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (scalar_t__,char*,unsigned long long) ; 

void d_tmpfile(struct dentry *dentry, struct inode *inode)
{
	inode_dec_link_count(inode);
	BUG_ON(dentry->d_name.name != dentry->d_iname ||
		!hlist_unhashed(&dentry->d_u.d_alias) ||
		!d_unlinked(dentry));
	spin_lock(&dentry->d_parent->d_lock);
	spin_lock_nested(&dentry->d_lock, DENTRY_D_LOCK_NESTED);
	dentry->d_name.len = sprintf(dentry->d_iname, "#%llu",
				(unsigned long long)inode->i_ino);
	spin_unlock(&dentry->d_lock);
	spin_unlock(&dentry->d_parent->d_lock);
	d_instantiate(dentry, inode);
}