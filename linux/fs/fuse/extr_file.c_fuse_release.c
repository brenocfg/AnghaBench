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
struct fuse_conn {scalar_t__ writeback_cache; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_release_common (struct file*,int) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  write_inode_now (struct inode*,int) ; 

__attribute__((used)) static int fuse_release(struct inode *inode, struct file *file)
{
	struct fuse_conn *fc = get_fuse_conn(inode);

	/* see fuse_vma_close() for !writeback_cache case */
	if (fc->writeback_cache)
		write_inode_now(inode, 1);

	fuse_release_common(file, false);

	/* return value is ignored by VFS */
	return 0;
}