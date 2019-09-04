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
 int EINVAL ; 
 unsigned int RENAME_EXCHANGE ; 
 unsigned int RENAME_NOREPLACE ; 
 int gfs2_exchange (struct inode*,struct dentry*,struct inode*,struct dentry*,unsigned int) ; 
 int gfs2_rename (struct inode*,struct dentry*,struct inode*,struct dentry*) ; 

__attribute__((used)) static int gfs2_rename2(struct inode *odir, struct dentry *odentry,
			struct inode *ndir, struct dentry *ndentry,
			unsigned int flags)
{
	flags &= ~RENAME_NOREPLACE;

	if (flags & ~RENAME_EXCHANGE)
		return -EINVAL;

	if (flags & RENAME_EXCHANGE)
		return gfs2_exchange(odir, odentry, ndir, ndentry, flags);

	return gfs2_rename(odir, odentry, ndir, ndentry);
}