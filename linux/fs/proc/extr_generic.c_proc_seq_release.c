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
struct proc_dir_entry {scalar_t__ state_size; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct proc_dir_entry* PDE (struct inode*) ; 
 int seq_release (struct inode*,struct file*) ; 
 int seq_release_private (struct inode*,struct file*) ; 

__attribute__((used)) static int proc_seq_release(struct inode *inode, struct file *file)
{
	struct proc_dir_entry *de = PDE(inode);

	if (de->state_size)
		return seq_release_private(inode, file);
	return seq_release(inode, file);
}