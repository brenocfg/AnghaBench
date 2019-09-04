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
struct proc_dir_entry {int /*<<< orphan*/ * proc_iops; scalar_t__ data; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IFLNK ; 
 int S_IRUGO ; 
 int S_IWUGO ; 
 int S_IXUGO ; 
 struct proc_dir_entry* __proc_create (struct proc_dir_entry**,char const*,int,int) ; 
 scalar_t__ kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pde_free (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  proc_link_inode_operations ; 
 struct proc_dir_entry* proc_register (struct proc_dir_entry*,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

struct proc_dir_entry *proc_symlink(const char *name,
		struct proc_dir_entry *parent, const char *dest)
{
	struct proc_dir_entry *ent;

	ent = __proc_create(&parent, name,
			  (S_IFLNK | S_IRUGO | S_IWUGO | S_IXUGO),1);

	if (ent) {
		ent->data = kmalloc((ent->size=strlen(dest))+1, GFP_KERNEL);
		if (ent->data) {
			strcpy((char*)ent->data,dest);
			ent->proc_iops = &proc_link_inode_operations;
			ent = proc_register(parent, ent);
		} else {
			pde_free(ent);
			ent = NULL;
		}
	}
	return ent;
}