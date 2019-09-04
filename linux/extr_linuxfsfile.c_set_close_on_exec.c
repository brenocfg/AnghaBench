#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct files_struct {int /*<<< orphan*/  file_lock; } ;
struct fdtable {int dummy; } ;
struct TYPE_2__ {struct files_struct* files; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_close_on_exec (unsigned int,struct fdtable*) ; 
 int /*<<< orphan*/  __set_close_on_exec (unsigned int,struct fdtable*) ; 
 TYPE_1__* current ; 
 struct fdtable* files_fdtable (struct files_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void set_close_on_exec(unsigned int fd, int flag)
{
	struct files_struct *files = current->files;
	struct fdtable *fdt;
	spin_lock(&files->file_lock);
	fdt = files_fdtable(files);
	if (flag)
		__set_close_on_exec(fd, fdt);
	else
		__clear_close_on_exec(fd, fdt);
	spin_unlock(&files->file_lock);
}