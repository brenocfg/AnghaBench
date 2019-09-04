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
struct files_struct {int /*<<< orphan*/  file_lock; } ;
struct file {int dummy; } ;
struct fdtable {unsigned int max_fds; unsigned long* close_on_exec; struct file** fd; } ;

/* Variables and functions */
 unsigned int BITS_PER_LONG ; 
 int /*<<< orphan*/  __put_unused_fd (struct files_struct*,unsigned int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct fdtable* files_fdtable (struct files_struct*) ; 
 int /*<<< orphan*/  filp_close (struct file*,struct files_struct*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void do_close_on_exec(struct files_struct *files)
{
	unsigned i;
	struct fdtable *fdt;

	/* exec unshares first */
	spin_lock(&files->file_lock);
	for (i = 0; ; i++) {
		unsigned long set;
		unsigned fd = i * BITS_PER_LONG;
		fdt = files_fdtable(files);
		if (fd >= fdt->max_fds)
			break;
		set = fdt->close_on_exec[i];
		if (!set)
			continue;
		fdt->close_on_exec[i] = 0;
		for ( ; set ; fd++, set >>= 1) {
			struct file *file;
			if (!(set & 1))
				continue;
			file = fdt->fd[fd];
			if (!file)
				continue;
			rcu_assign_pointer(fdt->fd[fd], NULL);
			__put_unused_fd(files, fd);
			spin_unlock(&files->file_lock);
			filp_close(file, files);
			cond_resched();
			spin_lock(&files->file_lock);
		}

	}
	spin_unlock(&files->file_lock);
}