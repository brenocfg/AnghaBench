#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;
struct cifsFileInfo {int /*<<< orphan*/  tlink; } ;
struct TYPE_2__ {scalar_t__ unix_ext; } ;

/* Variables and functions */
 int cifs_get_file_info (struct file*) ; 
 int cifs_get_file_info_unix (struct file*) ; 
 int /*<<< orphan*/  cifs_inode_needs_reval (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 TYPE_1__* tlink_tcon (int /*<<< orphan*/ ) ; 

int cifs_revalidate_file_attr(struct file *filp)
{
	int rc = 0;
	struct inode *inode = file_inode(filp);
	struct cifsFileInfo *cfile = (struct cifsFileInfo *) filp->private_data;

	if (!cifs_inode_needs_reval(inode))
		return rc;

	if (tlink_tcon(cfile->tlink)->unix_ext)
		rc = cifs_get_file_info_unix(filp);
	else
		rc = cifs_get_file_info(filp);

	return rc;
}