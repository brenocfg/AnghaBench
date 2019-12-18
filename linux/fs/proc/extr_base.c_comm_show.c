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
struct task_struct {int dummy; } ;
struct seq_file {struct inode* private; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ESRCH ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 int /*<<< orphan*/  proc_task_name (struct seq_file*,struct task_struct*,int) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int comm_show(struct seq_file *m, void *v)
{
	struct inode *inode = m->private;
	struct task_struct *p;

	p = get_proc_task(inode);
	if (!p)
		return -ESRCH;

	proc_task_name(m, p, false);
	seq_putc(m, '\n');

	put_task_struct(p);

	return 0;
}