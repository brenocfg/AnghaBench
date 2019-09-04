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
struct threads {int /*<<< orphan*/  lock; } ;
struct machine {struct threads* threads; int /*<<< orphan*/  current_tid; int /*<<< orphan*/  mmap_name; int /*<<< orphan*/  root_dir; int /*<<< orphan*/  dsos; int /*<<< orphan*/  kmaps; } ;

/* Variables and functions */
 int THREADS__TABLE_SIZE ; 
 int /*<<< orphan*/  dsos__exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  machine__destroy_kernel_maps (struct machine*) ; 
 int /*<<< orphan*/  machine__exit_vdso (struct machine*) ; 
 int /*<<< orphan*/  map_groups__exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

void machine__exit(struct machine *machine)
{
	int i;

	if (machine == NULL)
		return;

	machine__destroy_kernel_maps(machine);
	map_groups__exit(&machine->kmaps);
	dsos__exit(&machine->dsos);
	machine__exit_vdso(machine);
	zfree(&machine->root_dir);
	zfree(&machine->mmap_name);
	zfree(&machine->current_tid);

	for (i = 0; i < THREADS__TABLE_SIZE; i++) {
		struct threads *threads = &machine->threads[i];
		exit_rwsem(&threads->lock);
	}
}