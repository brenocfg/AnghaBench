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
struct machine {int /*<<< orphan*/ * mmap_name; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ asprintf (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ machine__is_default_guest (struct machine*) ; 
 scalar_t__ machine__is_host (struct machine*) ; 
 void* strdup (char*) ; 

__attribute__((used)) static int machine__set_mmap_name(struct machine *machine)
{
	if (machine__is_host(machine))
		machine->mmap_name = strdup("[kernel.kallsyms]");
	else if (machine__is_default_guest(machine))
		machine->mmap_name = strdup("[guest.kernel.kallsyms]");
	else if (asprintf(&machine->mmap_name, "[guest.kernel.kallsyms.%d]",
			  machine->pid) < 0)
		machine->mmap_name = NULL;

	return machine->mmap_name ? 0 : -ENOMEM;
}