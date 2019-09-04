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
struct trace_subsystem_dir {scalar_t__ subsystem; int /*<<< orphan*/  tr; } ;
struct inode {int dummy; } ;
struct file {struct trace_subsystem_dir* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct trace_subsystem_dir*) ; 
 int /*<<< orphan*/  put_system (struct trace_subsystem_dir*) ; 
 int /*<<< orphan*/  trace_array_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int subsystem_release(struct inode *inode, struct file *file)
{
	struct trace_subsystem_dir *dir = file->private_data;

	trace_array_put(dir->tr);

	/*
	 * If dir->subsystem is NULL, then this is a temporary
	 * descriptor that was made for a trace_array to enable
	 * all subsystems.
	 */
	if (dir->subsystem)
		put_system(dir);
	else
		kfree(dir);

	return 0;
}