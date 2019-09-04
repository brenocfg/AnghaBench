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
struct proc_dir_entry {int /*<<< orphan*/  nlink; int /*<<< orphan*/ * proc_iops; int /*<<< orphan*/ * proc_fops; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 struct proc_dir_entry* __proc_create (struct proc_dir_entry**,char const*,int,int) ; 
 struct proc_dir_entry* proc_register (struct proc_dir_entry*,struct proc_dir_entry*) ; 

struct proc_dir_entry *proc_create_mount_point(const char *name)
{
	umode_t mode = S_IFDIR | S_IRUGO | S_IXUGO;
	struct proc_dir_entry *ent, *parent = NULL;

	ent = __proc_create(&parent, name, mode, 2);
	if (ent) {
		ent->data = NULL;
		ent->proc_fops = NULL;
		ent->proc_iops = NULL;
		parent->nlink++;
		ent = proc_register(parent, ent);
		if (!ent)
			parent->nlink--;
	}
	return ent;
}