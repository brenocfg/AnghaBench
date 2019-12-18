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
struct seq_file {struct proc_mounts* private; } ;
struct proc_mounts {int /*<<< orphan*/  ns; int /*<<< orphan*/  root; } ;
struct inode {int dummy; } ;
struct file {struct seq_file* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_mnt_ns (int /*<<< orphan*/ ) ; 
 int seq_release_private (struct inode*,struct file*) ; 

__attribute__((used)) static int mounts_release(struct inode *inode, struct file *file)
{
	struct seq_file *m = file->private_data;
	struct proc_mounts *p = m->private;
	path_put(&p->root);
	put_mnt_ns(p->ns);
	return seq_release_private(inode, file);
}