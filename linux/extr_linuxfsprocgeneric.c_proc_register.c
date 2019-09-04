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
struct proc_dir_entry {int /*<<< orphan*/  low_ino; int /*<<< orphan*/  name; struct proc_dir_entry* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pde_free (struct proc_dir_entry*) ; 
 int pde_subdir_insert (struct proc_dir_entry*,struct proc_dir_entry*) ; 
 scalar_t__ proc_alloc_inum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_free_inum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_subdir_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

struct proc_dir_entry *proc_register(struct proc_dir_entry *dir,
		struct proc_dir_entry *dp)
{
	if (proc_alloc_inum(&dp->low_ino))
		goto out_free_entry;

	write_lock(&proc_subdir_lock);
	dp->parent = dir;
	if (pde_subdir_insert(dir, dp) == false) {
		WARN(1, "proc_dir_entry '%s/%s' already registered\n",
		     dir->name, dp->name);
		write_unlock(&proc_subdir_lock);
		goto out_free_inum;
	}
	write_unlock(&proc_subdir_lock);

	return dp;
out_free_inum:
	proc_free_inum(dp->low_ino);
out_free_entry:
	pde_free(dp);
	return NULL;
}