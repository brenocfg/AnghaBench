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
typedef  int umode_t ;
struct proc_dir_entry {int /*<<< orphan*/  nlink; int /*<<< orphan*/ * proc_iops; int /*<<< orphan*/ * proc_fops; void* data; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 struct proc_dir_entry* __proc_create (struct proc_dir_entry**,char const*,int,int) ; 
 int /*<<< orphan*/  proc_dir_inode_operations ; 
 int /*<<< orphan*/  proc_dir_operations ; 
 struct proc_dir_entry* proc_register (struct proc_dir_entry*,struct proc_dir_entry*) ; 

struct proc_dir_entry *proc_mkdir_data(const char *name, umode_t mode,
		struct proc_dir_entry *parent, void *data)
{
	struct proc_dir_entry *ent;

	if (mode == 0)
		mode = S_IRUGO | S_IXUGO;

	ent = __proc_create(&parent, name, S_IFDIR | mode, 2);
	if (ent) {
		ent->data = data;
		ent->proc_fops = &proc_dir_operations;
		ent->proc_iops = &proc_dir_inode_operations;
		parent->nlink++;
		ent = proc_register(parent, ent);
		if (!ent)
			parent->nlink--;
	}
	return ent;
}