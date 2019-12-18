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
struct machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  machine__delete (struct machine*) ; 
 scalar_t__ machine__load_kallsyms (struct machine*,char*) ; 
 struct machine* machine__new_host () ; 

struct machine *machine__new_kallsyms(void)
{
	struct machine *machine = machine__new_host();
	/*
	 * FIXME:
	 * 1) We should switch to machine__load_kallsyms(), i.e. not explicitly
	 *    ask for not using the kcore parsing code, once this one is fixed
	 *    to create a map per module.
	 */
	if (machine && machine__load_kallsyms(machine, "/proc/kallsyms") <= 0) {
		machine__delete(machine);
		machine = NULL;
	}

	return machine;
}