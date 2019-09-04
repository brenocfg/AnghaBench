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
typedef  int /*<<< orphan*/  umode_t ;
struct proc_dir_entry {struct file_operations const* proc_fops; } ;
struct file_operations {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct proc_dir_entry* proc_create_reg (char const*,int /*<<< orphan*/ ,struct proc_dir_entry**,void*) ; 
 struct proc_dir_entry* proc_register (struct proc_dir_entry*,struct proc_dir_entry*) ; 

struct proc_dir_entry *proc_create_data(const char *name, umode_t mode,
		struct proc_dir_entry *parent,
		const struct file_operations *proc_fops, void *data)
{
	struct proc_dir_entry *p;

	BUG_ON(proc_fops == NULL);

	p = proc_create_reg(name, mode, &parent, data);
	if (!p)
		return NULL;
	p->proc_fops = proc_fops;
	return proc_register(parent, p);
}