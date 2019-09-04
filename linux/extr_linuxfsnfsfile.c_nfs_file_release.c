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
 int /*<<< orphan*/  NFSIOS_VFSRELEASE ; 
 int /*<<< orphan*/  dprintk (char*,struct file*) ; 
 int /*<<< orphan*/  nfs_file_clear_open_context (struct file*) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 

int
nfs_file_release(struct inode *inode, struct file *filp)
{
	dprintk("NFS: release(%pD2)\n", filp);

	nfs_inc_stats(inode, NFSIOS_VFSRELEASE);
	nfs_file_clear_open_context(filp);
	return 0;
}