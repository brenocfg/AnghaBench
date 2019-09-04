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
struct seq_operations {int dummy; } ;
struct proc_dir_entry {unsigned int state_size; struct seq_operations const* seq_ops; int /*<<< orphan*/ * proc_fops; } ;

/* Variables and functions */
 int /*<<< orphan*/  pde_force_lookup (struct proc_dir_entry*) ; 
 struct proc_dir_entry* proc_create_reg (char const*,int /*<<< orphan*/ ,struct proc_dir_entry**,void*) ; 
 int /*<<< orphan*/  proc_net_seq_fops ; 
 struct proc_dir_entry* proc_register (struct proc_dir_entry*,struct proc_dir_entry*) ; 

struct proc_dir_entry *proc_create_net_data(const char *name, umode_t mode,
		struct proc_dir_entry *parent, const struct seq_operations *ops,
		unsigned int state_size, void *data)
{
	struct proc_dir_entry *p;

	p = proc_create_reg(name, mode, &parent, data);
	if (!p)
		return NULL;
	pde_force_lookup(p);
	p->proc_fops = &proc_net_seq_fops;
	p->seq_ops = ops;
	p->state_size = state_size;
	return proc_register(parent, p);
}