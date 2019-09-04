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
struct trace_subsystem_dir {int /*<<< orphan*/  list; int /*<<< orphan*/  entry; int /*<<< orphan*/  nr_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  __put_system_dir (struct trace_subsystem_dir*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracefs_remove_recursive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_subsystem(struct trace_subsystem_dir *dir)
{
	if (!dir)
		return;

	if (!--dir->nr_events) {
		tracefs_remove_recursive(dir->entry);
		list_del(&dir->list);
		__put_system_dir(dir);
	}
}