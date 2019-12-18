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
struct arch {unsigned int family; unsigned int model; } ;

/* Variables and functions */
 int sscanf (char*,char*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int x86__cpuid_parse(struct arch *arch, char *cpuid)
{
	unsigned int family, model, stepping;
	int ret;

	/*
	 * cpuid = "GenuineIntel,family,model,stepping"
	 */
	ret = sscanf(cpuid, "%*[^,],%u,%u,%u", &family, &model, &stepping);
	if (ret == 3) {
		arch->family = family;
		arch->model = model;
		return 0;
	}

	return -1;
}