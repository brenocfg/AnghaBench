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
struct proc_dir_entry {int /*<<< orphan*/  seq_ops; scalar_t__ state_size; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct proc_dir_entry* PDE (struct inode*) ; 
 int seq_open (struct file*,int /*<<< orphan*/ ) ; 
 int seq_open_private (struct file*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int proc_seq_open(struct inode *inode, struct file *file)
{
	struct proc_dir_entry *de = PDE(inode);

	if (de->state_size)
		return seq_open_private(file, de->seq_ops, de->state_size);
	return seq_open(file, de->seq_ops);
}