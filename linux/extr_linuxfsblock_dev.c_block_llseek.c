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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct inode* bdev_file_inode (struct file*) ; 
 int /*<<< orphan*/  fixed_size_llseek (struct file*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 

__attribute__((used)) static loff_t block_llseek(struct file *file, loff_t offset, int whence)
{
	struct inode *bd_inode = bdev_file_inode(file);
	loff_t retval;

	inode_lock(bd_inode);
	retval = fixed_size_llseek(file, offset, whence, i_size_read(bd_inode));
	inode_unlock(bd_inode);
	return retval;
}