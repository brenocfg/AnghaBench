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
struct arch {int family; int model; } ;

/* Variables and functions */
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static bool x86__ins_is_fused(struct arch *arch, const char *ins1,
			      const char *ins2)
{
	if (arch->family != 6 || arch->model < 0x1e || strstr(ins2, "jmp"))
		return false;

	if (arch->model == 0x1e) {
		/* Nehalem */
		if ((strstr(ins1, "cmp") && !strstr(ins1, "xchg")) ||
		     strstr(ins1, "test")) {
			return true;
		}
	} else {
		/* Newer platform */
		if ((strstr(ins1, "cmp") && !strstr(ins1, "xchg")) ||
		     strstr(ins1, "test") ||
		     strstr(ins1, "add") ||
		     strstr(ins1, "sub") ||
		     strstr(ins1, "and") ||
		     strstr(ins1, "inc") ||
		     strstr(ins1, "dec")) {
			return true;
		}
	}

	return false;
}