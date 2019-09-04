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
struct proc_dir_entry {int (* single_show ) (struct seq_file*,void*) ;int /*<<< orphan*/ * proc_fops; } ;

/* Variables and functions */
 int /*<<< orphan*/  pde_force_lookup (struct proc_dir_entry*) ; 
 struct proc_dir_entry* proc_create_reg (char const*,int /*<<< orphan*/ ,struct proc_dir_entry**,void*) ; 
 int /*<<< orphan*/  proc_net_single_fops ; 
 struct proc_dir_entry* proc_register (struct proc_dir_entry*,struct proc_dir_entry*) ; 

struct proc_dir_entry *proc_create_net_single(const char *name, umode_t mode,
		struct proc_dir_entry *parent,
		int (*show)(struct seq_file *, void *), void *data)
{
	struct proc_dir_entry *p;

	p = proc_create_reg(name, mode, &parent, data);
	if (!p)
		return NULL;
	pde_force_lookup(p);
	p->proc_fops = &proc_net_single_fops;
	p->single_show = show;
	return proc_register(parent, p);
}