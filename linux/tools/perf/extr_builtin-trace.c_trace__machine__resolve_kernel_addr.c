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
struct machine {int kptr_restrict_warned; } ;
struct TYPE_2__ {scalar_t__ kptr_restrict; } ;

/* Variables and functions */
 char* machine__resolve_kernel_addr (void*,unsigned long long*,char**) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static char *trace__machine__resolve_kernel_addr(void *vmachine, unsigned long long *addrp, char **modp)
{
	struct machine *machine = vmachine;

	if (machine->kptr_restrict_warned)
		return NULL;

	if (symbol_conf.kptr_restrict) {
		pr_warning("Kernel address maps (/proc/{kallsyms,modules}) are restricted.\n\n"
			   "Check /proc/sys/kernel/kptr_restrict and /proc/sys/kernel/perf_event_paranoid.\n\n"
			   "Kernel samples will not be resolved.\n");
		machine->kptr_restrict_warned = true;
		return NULL;
	}

	return machine__resolve_kernel_addr(vmachine, addrp, modp);
}