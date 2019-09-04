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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct file {int f_mode; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,struct inode*,struct file*,int) ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 

int cifs_flush(struct file *file, fl_owner_t id)
{
	struct inode *inode = file_inode(file);
	int rc = 0;

	if (file->f_mode & FMODE_WRITE)
		rc = filemap_write_and_wait(inode->i_mapping);

	cifs_dbg(FYI, "Flush inode %p file %p rc %d\n", inode, file, rc);

	return rc;
}