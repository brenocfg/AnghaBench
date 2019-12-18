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
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct file* lower_file; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_1__* ecryptfs_inode_to_private (struct inode*) ; 
 int kernel_read (struct file*,char*,size_t,int /*<<< orphan*/ *) ; 

int ecryptfs_read_lower(char *data, loff_t offset, size_t size,
			struct inode *ecryptfs_inode)
{
	struct file *lower_file;
	lower_file = ecryptfs_inode_to_private(ecryptfs_inode)->lower_file;
	if (!lower_file)
		return -EIO;
	return kernel_read(lower_file, data, size, &offset);
}