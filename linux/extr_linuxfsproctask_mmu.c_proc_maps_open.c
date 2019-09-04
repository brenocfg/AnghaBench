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
struct seq_operations {int dummy; } ;
struct proc_maps_private {int /*<<< orphan*/  mm; struct inode* inode; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTRACE_MODE_READ ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct proc_maps_private* __seq_open_private (struct file*,struct seq_operations const*,int) ; 
 int /*<<< orphan*/  proc_mem_open (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_release_private (struct inode*,struct file*) ; 

__attribute__((used)) static int proc_maps_open(struct inode *inode, struct file *file,
			const struct seq_operations *ops, int psize)
{
	struct proc_maps_private *priv = __seq_open_private(file, ops, psize);

	if (!priv)
		return -ENOMEM;

	priv->inode = inode;
	priv->mm = proc_mem_open(inode, PTRACE_MODE_READ);
	if (IS_ERR(priv->mm)) {
		int err = PTR_ERR(priv->mm);

		seq_release_private(inode, file);
		return err;
	}

	return 0;
}