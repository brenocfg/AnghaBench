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
 int nfs_lookup_revalidate_done (struct inode*,struct dentry*,struct inode*,int) ; 
 int /*<<< orphan*/  nfs_save_change_attribute (struct inode*) ; 
 int /*<<< orphan*/  nfs_set_verifier (struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_lookup_revalidate_delegated(struct inode *dir, struct dentry *dentry,
				struct inode *inode)
{
	nfs_set_verifier(dentry, nfs_save_change_attribute(dir));
	return nfs_lookup_revalidate_done(dir, dentry, inode, 1);
}