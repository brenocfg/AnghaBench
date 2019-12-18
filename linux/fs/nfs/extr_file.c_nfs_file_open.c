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
struct file {int /*<<< orphan*/  f_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSIOS_VFSOPEN ; 
 int /*<<< orphan*/  dprintk (char*,struct file*) ; 
 int nfs_check_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_open (struct inode*,struct file*) ; 

__attribute__((used)) static int
nfs_file_open(struct inode *inode, struct file *filp)
{
	int res;

	dprintk("NFS: open file(%pD2)\n", filp);

	nfs_inc_stats(inode, NFSIOS_VFSOPEN);
	res = nfs_check_flags(filp->f_flags);
	if (res)
		return res;

	res = nfs_open(inode, filp);
	return res;
}