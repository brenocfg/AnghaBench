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
struct arch {int initialized; } ;

/* Variables and functions */
 int SYMBOL_ANNOTATE_ERRNO__ARCH_INIT_CPUID_PARSING ; 
 scalar_t__ x86__cpuid_parse (struct arch*,char*) ; 

__attribute__((used)) static int x86__annotate_init(struct arch *arch, char *cpuid)
{
	int err = 0;

	if (arch->initialized)
		return 0;

	if (cpuid) {
		if (x86__cpuid_parse(arch, cpuid))
			err = SYMBOL_ANNOTATE_ERRNO__ARCH_INIT_CPUID_PARSING;
	}

	arch->initialized = true;
	return err;
}