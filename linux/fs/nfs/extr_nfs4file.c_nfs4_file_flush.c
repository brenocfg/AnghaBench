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
struct file {int f_mode; int /*<<< orphan*/  f_mapping; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int /*<<< orphan*/  NFSIOS_VFSFLUSH ; 
 int /*<<< orphan*/  dprintk (char*,struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_fdatawrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_delegation_flush_on_close (struct inode*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_wb_all (struct inode*) ; 

__attribute__((used)) static int
nfs4_file_flush(struct file *file, fl_owner_t id)
{
	struct inode	*inode = file_inode(file);

	dprintk("NFS: flush(%pD2)\n", file);

	nfs_inc_stats(inode, NFSIOS_VFSFLUSH);
	if ((file->f_mode & FMODE_WRITE) == 0)
		return 0;

	/*
	 * If we're holding a write delegation, then check if we're required
	 * to flush the i/o on close. If not, then just start the i/o now.
	 */
	if (!nfs4_delegation_flush_on_close(inode))
		return filemap_fdatawrite(file->f_mapping);

	/* Flush writes to the server and return any errors */
	return nfs_wb_all(inode);
}