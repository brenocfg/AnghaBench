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
struct file {int dummy; } ;

/* Variables and functions */
 int cifs_revalidate_file_attr (struct file*) ; 
 int cifs_revalidate_mapping (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 

int cifs_revalidate_file(struct file *filp)
{
	int rc;
	struct inode *inode = file_inode(filp);

	rc = cifs_revalidate_file_attr(filp);
	if (rc)
		return rc;

	return cifs_revalidate_mapping(inode);
}