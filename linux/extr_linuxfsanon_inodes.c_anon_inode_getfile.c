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
struct file_operations {scalar_t__ owner; } ;
struct file {void* private_data; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 struct file* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int O_ACCMODE ; 
 int O_NONBLOCK ; 
 struct file* alloc_file_pseudo (struct file*,int /*<<< orphan*/ ,char const*,int,struct file_operations const*) ; 
 struct file* anon_inode_inode ; 
 int /*<<< orphan*/  anon_inode_mnt ; 
 int /*<<< orphan*/  ihold (struct file*) ; 
 int /*<<< orphan*/  iput (struct file*) ; 
 int /*<<< orphan*/  module_put (scalar_t__) ; 
 int /*<<< orphan*/  try_module_get (scalar_t__) ; 

struct file *anon_inode_getfile(const char *name,
				const struct file_operations *fops,
				void *priv, int flags)
{
	struct file *file;

	if (IS_ERR(anon_inode_inode))
		return ERR_PTR(-ENODEV);

	if (fops->owner && !try_module_get(fops->owner))
		return ERR_PTR(-ENOENT);

	/*
	 * We know the anon_inode inode count is always greater than zero,
	 * so ihold() is safe.
	 */
	ihold(anon_inode_inode);
	file = alloc_file_pseudo(anon_inode_inode, anon_inode_mnt, name,
				 flags & (O_ACCMODE | O_NONBLOCK), fops);
	if (IS_ERR(file))
		goto err;

	file->f_mapping = anon_inode_inode->i_mapping;

	file->private_data = priv;

	return file;

err:
	iput(anon_inode_inode);
	module_put(fops->owner);
	return file;
}