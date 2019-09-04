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
struct proc_dir_entry {scalar_t__ nlink; int /*<<< orphan*/  mode; struct proc_dir_entry* parent; int /*<<< orphan*/  subdir; int /*<<< orphan*/  subdir_node; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ __xlate_proc_name (char const*,struct proc_dir_entry**,char const**) ; 
 int /*<<< orphan*/  pde_put (struct proc_dir_entry*) ; 
 struct proc_dir_entry* pde_subdir_find (struct proc_dir_entry*,char const*,unsigned int) ; 
 struct proc_dir_entry* pde_subdir_first (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  proc_entry_rundown (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  proc_subdir_lock ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int strlen (char const*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int remove_proc_subtree(const char *name, struct proc_dir_entry *parent)
{
	struct proc_dir_entry *root = NULL, *de, *next;
	const char *fn = name;
	unsigned int len;

	write_lock(&proc_subdir_lock);
	if (__xlate_proc_name(name, &parent, &fn) != 0) {
		write_unlock(&proc_subdir_lock);
		return -ENOENT;
	}
	len = strlen(fn);

	root = pde_subdir_find(parent, fn, len);
	if (!root) {
		write_unlock(&proc_subdir_lock);
		return -ENOENT;
	}
	rb_erase(&root->subdir_node, &parent->subdir);

	de = root;
	while (1) {
		next = pde_subdir_first(de);
		if (next) {
			rb_erase(&next->subdir_node, &de->subdir);
			de = next;
			continue;
		}
		write_unlock(&proc_subdir_lock);

		proc_entry_rundown(de);
		next = de->parent;
		if (S_ISDIR(de->mode))
			next->nlink--;
		de->nlink = 0;
		if (de == root)
			break;
		pde_put(de);

		write_lock(&proc_subdir_lock);
		de = next;
	}
	pde_put(root);
	return 0;
}