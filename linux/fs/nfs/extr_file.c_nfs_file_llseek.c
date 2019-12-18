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
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int SEEK_CUR ; 
 int SEEK_SET ; 
 int /*<<< orphan*/  dprintk (char*,struct file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  generic_file_llseek (struct file*,int /*<<< orphan*/ ,int) ; 
 int nfs_revalidate_file_size (struct inode*,struct file*) ; 

loff_t nfs_file_llseek(struct file *filp, loff_t offset, int whence)
{
	dprintk("NFS: llseek file(%pD2, %lld, %d)\n",
			filp, offset, whence);

	/*
	 * whence == SEEK_END || SEEK_DATA || SEEK_HOLE => we must revalidate
	 * the cached file length
	 */
	if (whence != SEEK_SET && whence != SEEK_CUR) {
		struct inode *inode = filp->f_mapping->host;

		int retval = nfs_revalidate_file_size(inode, filp);
		if (retval < 0)
			return (loff_t)retval;
	}

	return generic_file_llseek(filp, offset, whence);
}