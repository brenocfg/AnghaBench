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
struct nfs_open_dir_context {scalar_t__ duped; scalar_t__ dir_cookie; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ f_pos; struct nfs_open_dir_context* private_data; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  FILE ; 
#define  SEEK_CUR 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct file*,scalar_t__,int) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static loff_t nfs_llseek_dir(struct file *filp, loff_t offset, int whence)
{
	struct inode *inode = file_inode(filp);
	struct nfs_open_dir_context *dir_ctx = filp->private_data;

	dfprintk(FILE, "NFS: llseek dir(%pD2, %lld, %d)\n",
			filp, offset, whence);

	switch (whence) {
	default:
		return -EINVAL;
	case SEEK_SET:
		if (offset < 0)
			return -EINVAL;
		inode_lock(inode);
		break;
	case SEEK_CUR:
		if (offset == 0)
			return filp->f_pos;
		inode_lock(inode);
		offset += filp->f_pos;
		if (offset < 0) {
			inode_unlock(inode);
			return -EINVAL;
		}
	}
	if (offset != filp->f_pos) {
		filp->f_pos = offset;
		dir_ctx->dir_cookie = 0;
		dir_ctx->duped = 0;
	}
	inode_unlock(inode);
	return offset;
}