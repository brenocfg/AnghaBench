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
struct arch {unsigned int family; scalar_t__ model; } ;

/* Variables and functions */
 int sscanf (char*,char*,unsigned int*,char*,char*,char*,char*) ; 

__attribute__((used)) static int s390__cpuid_parse(struct arch *arch, char *cpuid)
{
	unsigned int family;
	char model[16], model_c[16], cpumf_v[16], cpumf_a[16];
	int ret;

	/*
	 * cpuid string format:
	 * "IBM,family,model-capacity,model[,cpum_cf-version,cpum_cf-authorization]"
	 */
	ret = sscanf(cpuid, "%*[^,],%u,%[^,],%[^,],%[^,],%s", &family, model_c,
		     model, cpumf_v, cpumf_a);
	if (ret >= 2) {
		arch->family = family;
		arch->model = 0;
		return 0;
	}

	return -1;
}