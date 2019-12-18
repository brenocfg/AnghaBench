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
typedef  int /*<<< orphan*/  u64 ;
struct fuse_conn {scalar_t__ delete_stale; } ;
struct dentry {int d_flags; int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int DCACHE_OP_DELETE ; 
 int /*<<< orphan*/  __fuse_dentry_settime (struct dentry*,int /*<<< orphan*/ ) ; 
 struct fuse_conn* get_fuse_conn_super (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_dentry_settime(struct dentry *dentry, u64 time)
{
	struct fuse_conn *fc = get_fuse_conn_super(dentry->d_sb);
	bool delete = !time && fc->delete_stale;
	/*
	 * Mess with DCACHE_OP_DELETE because dput() will be faster without it.
	 * Don't care about races, either way it's just an optimization
	 */
	if ((!delete && (dentry->d_flags & DCACHE_OP_DELETE)) ||
	    (delete && !(dentry->d_flags & DCACHE_OP_DELETE))) {
		spin_lock(&dentry->d_lock);
		if (!delete)
			dentry->d_flags &= ~DCACHE_OP_DELETE;
		else
			dentry->d_flags |= DCACHE_OP_DELETE;
		spin_unlock(&dentry->d_lock);
	}

	__fuse_dentry_settime(dentry, time);
}