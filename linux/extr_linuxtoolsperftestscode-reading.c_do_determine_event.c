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

/* Variables and functions */

__attribute__((used)) static const char *do_determine_event(bool excl_kernel)
{
	const char *event = excl_kernel ? "cycles:u" : "cycles";

#ifdef __s390x__
	char cpuid[128], model[16], model_c[16], cpum_cf_v[16];
	unsigned int family;
	int ret, cpum_cf_a;

	if (get_cpuid(cpuid, sizeof(cpuid)))
		goto out_clocks;
	ret = sscanf(cpuid, "%*[^,],%u,%[^,],%[^,],%[^,],%x", &family, model_c,
		     model, cpum_cf_v, &cpum_cf_a);
	if (ret != 5)		 /* Not available */
		goto out_clocks;
	if (excl_kernel && (cpum_cf_a & 4))
		return event;
	if (!excl_kernel && (cpum_cf_a & 2))
		return event;

	/* Fall through: missing authorization */
out_clocks:
	event = excl_kernel ? "cpu-clock:u" : "cpu-clock";

#endif
	return event;
}