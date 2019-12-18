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
struct seq_file {struct seq_operations* op; } ;
struct inode {int dummy; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct seq_operations const*) ; 
 int seq_release (struct inode*,struct file*) ; 

int single_release(struct inode *inode, struct file *file)
{
	const struct seq_operations *op = ((struct seq_file *)file->private_data)->op;
	int res = seq_release(inode, file);
	kfree(op);
	return res;
}