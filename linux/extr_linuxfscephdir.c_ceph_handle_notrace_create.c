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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ESTALE ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 struct dentry* ceph_lookup (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 

int ceph_handle_notrace_create(struct inode *dir, struct dentry *dentry)
{
	struct dentry *result = ceph_lookup(dir, dentry, 0);

	if (result && !IS_ERR(result)) {
		/*
		 * We created the item, then did a lookup, and found
		 * it was already linked to another inode we already
		 * had in our cache (and thus got spliced). To not
		 * confuse VFS (especially when inode is a directory),
		 * we don't link our dentry to that inode, return an
		 * error instead.
		 *
		 * This event should be rare and it happens only when
		 * we talk to old MDS. Recent MDS does not send traceless
		 * reply for request that creates new inode.
		 */
		d_drop(result);
		return -ESTALE;
	}
	return PTR_ERR(result);
}