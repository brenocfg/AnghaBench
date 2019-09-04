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
typedef  int /*<<< orphan*/  umode_t ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_size; } ;

/* Variables and functions */
 TYPE_1__* d_inode (struct dentry*) ; 
 struct dentry* debugfs_create_file (char const*,int /*<<< orphan*/ ,struct dentry*,void*,struct file_operations const*) ; 

struct dentry *debugfs_create_file_size(const char *name, umode_t mode,
					struct dentry *parent, void *data,
					const struct file_operations *fops,
					loff_t file_size)
{
	struct dentry *de = debugfs_create_file(name, mode, parent, data, fops);

	if (de)
		d_inode(de)->i_size = file_size;
	return de;
}