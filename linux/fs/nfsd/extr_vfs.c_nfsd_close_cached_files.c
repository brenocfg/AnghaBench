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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  nfsd_file_close_inode_sync (struct inode*) ; 

__attribute__((used)) static void
nfsd_close_cached_files(struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);

	if (inode && S_ISREG(inode->i_mode))
		nfsd_file_close_inode_sync(inode);
}