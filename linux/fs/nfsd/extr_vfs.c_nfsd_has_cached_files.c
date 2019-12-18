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
 int nfsd_file_is_cached (struct inode*) ; 

__attribute__((used)) static bool
nfsd_has_cached_files(struct dentry *dentry)
{
	bool		ret = false;
	struct inode *inode = d_inode(dentry);

	if (inode && S_ISREG(inode->i_mode))
		ret = nfsd_file_is_cached(inode);
	return ret;
}