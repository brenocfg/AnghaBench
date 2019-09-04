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
struct proc_dir_entry {int /*<<< orphan*/  data; int /*<<< orphan*/  single_show; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct proc_dir_entry* PDE (struct inode*) ; 
 int single_open (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_single_open(struct inode *inode, struct file *file)
{
	struct proc_dir_entry *de = PDE(inode);

	return single_open(file, de->single_show, de->data);
}