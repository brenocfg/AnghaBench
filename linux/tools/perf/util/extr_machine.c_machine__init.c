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
struct thread {int dummy; } ;
struct machine {int pid; int kptr_restrict_warned; int comm_exec; int /*<<< orphan*/ * mmap_name; int /*<<< orphan*/ * root_dir; int /*<<< orphan*/ * current_tid; int /*<<< orphan*/ * vmlinux_map; scalar_t__ kernel_start; scalar_t__ id_hdr_size; int /*<<< orphan*/ * env; int /*<<< orphan*/ * vdso_info; int /*<<< orphan*/  dsos; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  kmaps; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  comm ;

/* Variables and functions */
 int ENOMEM ; 
 int HOST_KERNEL_ID ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsos__init (int /*<<< orphan*/ *) ; 
 struct thread* machine__findnew_thread (struct machine*,int,int) ; 
 scalar_t__ machine__set_mmap_name (struct machine*) ; 
 int /*<<< orphan*/  machine__threads_init (struct machine*) ; 
 int /*<<< orphan*/  map_groups__init (int /*<<< orphan*/ *,struct machine*) ; 
 int /*<<< orphan*/  memset (struct machine*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 
 int /*<<< orphan*/  thread__set_comm (struct thread*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

int machine__init(struct machine *machine, const char *root_dir, pid_t pid)
{
	int err = -ENOMEM;

	memset(machine, 0, sizeof(*machine));
	map_groups__init(&machine->kmaps, machine);
	RB_CLEAR_NODE(&machine->rb_node);
	dsos__init(&machine->dsos);

	machine__threads_init(machine);

	machine->vdso_info = NULL;
	machine->env = NULL;

	machine->pid = pid;

	machine->id_hdr_size = 0;
	machine->kptr_restrict_warned = false;
	machine->comm_exec = false;
	machine->kernel_start = 0;
	machine->vmlinux_map = NULL;

	machine->root_dir = strdup(root_dir);
	if (machine->root_dir == NULL)
		return -ENOMEM;

	if (machine__set_mmap_name(machine))
		goto out;

	if (pid != HOST_KERNEL_ID) {
		struct thread *thread = machine__findnew_thread(machine, -1,
								pid);
		char comm[64];

		if (thread == NULL)
			goto out;

		snprintf(comm, sizeof(comm), "[guest/%d]", pid);
		thread__set_comm(thread, comm, 0);
		thread__put(thread);
	}

	machine->current_tid = NULL;
	err = 0;

out:
	if (err) {
		zfree(&machine->root_dir);
		zfree(&machine->mmap_name);
	}
	return 0;
}