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
 int cifs_revalidate_dentry_attr (struct dentry*) ; 
 int cifs_revalidate_mapping (struct inode*) ; 
 struct inode* d_inode (struct dentry*) ; 

int cifs_revalidate_dentry(struct dentry *dentry)
{
	int rc;
	struct inode *inode = d_inode(dentry);

	rc = cifs_revalidate_dentry_attr(dentry);
	if (rc)
		return rc;

	return cifs_revalidate_mapping(inode);
}