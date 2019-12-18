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
 scalar_t__ debug ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int genuine_intel ; 
 int /*<<< orphan*/  get_cpuid_or_exit (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 scalar_t__ has_epb ; 
 scalar_t__ has_hwp ; 
 int has_hwp_activity_window ; 
 int has_hwp_epp ; 
 int has_hwp_notify ; 
 int has_hwp_request_pkg ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ turbo_is_enabled ; 
 scalar_t__ update_hwp_use_pkg ; 

void parse_cpuid(void)
{
	unsigned int eax, ebx, ecx, edx, max_level;
	unsigned int fms, family, model, stepping;

	eax = ebx = ecx = edx = 0;

	get_cpuid_or_exit(0, &max_level, &ebx, &ecx, &edx);

	if (ebx == 0x756e6547 && edx == 0x49656e69 && ecx == 0x6c65746e)
		genuine_intel = 1;

	if (debug)
		fprintf(stderr, "CPUID(0): %.4s%.4s%.4s ",
			(char *)&ebx, (char *)&edx, (char *)&ecx);

	get_cpuid_or_exit(1, &fms, &ebx, &ecx, &edx);
	family = (fms >> 8) & 0xf;
	model = (fms >> 4) & 0xf;
	stepping = fms & 0xf;
	if (family == 6 || family == 0xf)
		model += ((fms >> 16) & 0xf) << 4;

	if (debug) {
		fprintf(stderr, "%d CPUID levels; family:model:stepping 0x%x:%x:%x (%d:%d:%d)\n",
			max_level, family, model, stepping, family, model, stepping);
		fprintf(stderr, "CPUID(1): %s %s %s %s %s %s %s %s\n",
			ecx & (1 << 0) ? "SSE3" : "-",
			ecx & (1 << 3) ? "MONITOR" : "-",
			ecx & (1 << 7) ? "EIST" : "-",
			ecx & (1 << 8) ? "TM2" : "-",
			edx & (1 << 4) ? "TSC" : "-",
			edx & (1 << 5) ? "MSR" : "-",
			edx & (1 << 22) ? "ACPI-TM" : "-",
			edx & (1 << 29) ? "TM" : "-");
	}

	if (!(edx & (1 << 5)))
		errx(1, "CPUID: no MSR");


	get_cpuid_or_exit(0x6, &eax, &ebx, &ecx, &edx);
	/* turbo_is_enabled already set */
	/* has_hwp already set */
	has_hwp_notify = eax & (1 << 8);
	has_hwp_activity_window = eax & (1 << 9);
	has_hwp_epp = eax & (1 << 10);
	has_hwp_request_pkg = eax & (1 << 11);

	if (!has_hwp_request_pkg && update_hwp_use_pkg)
		errx(1, "--hwp-use-pkg is not available on this hardware");

	/* has_epb already set */

	if (debug)
		fprintf(stderr,
			"CPUID(6): %sTURBO, %sHWP, %sHWPnotify, %sHWPwindow, %sHWPepp, %sHWPpkg, %sEPB\n",
			turbo_is_enabled ? "" : "No-",
			has_hwp ? "" : "No-",
			has_hwp_notify ? "" : "No-",
			has_hwp_activity_window ? "" : "No-",
			has_hwp_epp ? "" : "No-",
			has_hwp_request_pkg ? "" : "No-",
			has_epb ? "" : "No-");

	return;	/* success */
}