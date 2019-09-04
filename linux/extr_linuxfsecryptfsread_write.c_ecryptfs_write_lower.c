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
struct file {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct file* lower_file; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_1__* ecryptfs_inode_to_private (struct inode*) ; 
 int kernel_write (struct file*,char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (struct inode*) ; 

int ecryptfs_write_lower(struct inode *ecryptfs_inode, char *data,
			 loff_t offset, size_t size)
{
	struct file *lower_file;
	ssize_t rc;

	lower_file = ecryptfs_inode_to_private(ecryptfs_inode)->lower_file;
	if (!lower_file)
		return -EIO;
	rc = kernel_write(lower_file, data, size, &offset);
	mark_inode_dirty_sync(ecryptfs_inode);
	return rc;
}