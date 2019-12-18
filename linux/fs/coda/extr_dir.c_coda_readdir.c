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
struct file {TYPE_1__* f_op; } ;
struct dir_context {int dummy; } ;
struct coda_file_info {struct file* cfi_container; } ;
struct TYPE_2__ {int (* iterate ) (struct file*,struct dir_context*) ;int (* iterate_shared ) (struct file*,struct dir_context*) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  IS_DEADDIR (struct inode*) ; 
 struct coda_file_info* coda_ftoc (struct file*) ; 
 int coda_venus_readdir (struct file*,struct dir_context*) ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_lock_shared (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock_shared (struct inode*) ; 
 int stub1 (struct file*,struct dir_context*) ; 
 int stub2 (struct file*,struct dir_context*) ; 

__attribute__((used)) static int coda_readdir(struct file *coda_file, struct dir_context *ctx)
{
	struct coda_file_info *cfi;
	struct file *host_file;
	int ret;

	cfi = coda_ftoc(coda_file);
	host_file = cfi->cfi_container;

	if (host_file->f_op->iterate || host_file->f_op->iterate_shared) {
		struct inode *host_inode = file_inode(host_file);
		ret = -ENOENT;
		if (!IS_DEADDIR(host_inode)) {
			if (host_file->f_op->iterate_shared) {
				inode_lock_shared(host_inode);
				ret = host_file->f_op->iterate_shared(host_file, ctx);
				file_accessed(host_file);
				inode_unlock_shared(host_inode);
			} else {
				inode_lock(host_inode);
				ret = host_file->f_op->iterate(host_file, ctx);
				file_accessed(host_file);
				inode_unlock(host_inode);
			}
		}
		return ret;
	}
	/* Venus: we must read Venus dirents from a file */
	return coda_venus_readdir(coda_file, ctx);
}