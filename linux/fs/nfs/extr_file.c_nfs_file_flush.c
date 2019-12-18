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
struct file {int f_mode; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  NFSIOS_VFSFLUSH ; 
 int /*<<< orphan*/  dprintk (char*,struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_wb_all (struct inode*) ; 

__attribute__((used)) static int
nfs_file_flush(struct file *file, fl_owner_t id)
{
	struct inode	*inode = file_inode(file);

	dprintk("NFS: flush(%pD2)\n", file);

	nfs_inc_stats(inode, NFSIOS_VFSFLUSH);
	if ((file->f_mode & FMODE_WRITE) == 0)
		return 0;

	/* Flush writes to the server and return any errors */
	return nfs_wb_all(inode);
}