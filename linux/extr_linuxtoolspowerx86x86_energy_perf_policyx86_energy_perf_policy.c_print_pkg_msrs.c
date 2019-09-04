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
struct msr_hwp_request {int dummy; } ;
typedef  scalar_t__ msr ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_HWP_INTERRUPT ; 
 int /*<<< orphan*/  MSR_HWP_REQUEST_PKG ; 
 int /*<<< orphan*/  MSR_HWP_STATUS ; 
 int /*<<< orphan*/ * first_cpu_in_pkg ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,unsigned long long,char*,char*) ; 
 int /*<<< orphan*/  get_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  has_hwp ; 
 scalar_t__ has_hwp_notify ; 
 int /*<<< orphan*/  print_hwp_request_pkg (int,struct msr_hwp_request*,char*) ; 
 int /*<<< orphan*/  read_hwp_request (int /*<<< orphan*/ ,struct msr_hwp_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int print_pkg_msrs(int pkg)
{
	struct msr_hwp_request req;
	unsigned long long msr;

	if (!has_hwp)
		return 0;

	read_hwp_request(first_cpu_in_pkg[pkg], &req, MSR_HWP_REQUEST_PKG);
	print_hwp_request_pkg(pkg, &req, "");

	if (has_hwp_notify) {
		get_msr(first_cpu_in_pkg[pkg], MSR_HWP_INTERRUPT, &msr);
		fprintf(stderr,
		"pkg%d: MSR_HWP_INTERRUPT: 0x%08llx (Excursion_Min-%sabled, Guaranteed_Perf_Change-%sabled)\n",
		pkg, msr,
		((msr) & 0x2) ? "EN" : "Dis",
		((msr) & 0x1) ? "EN" : "Dis");
	}
	get_msr(first_cpu_in_pkg[pkg], MSR_HWP_STATUS, &msr);
	fprintf(stderr,
		"pkg%d: MSR_HWP_STATUS: 0x%08llx (%sExcursion_Min, %sGuaranteed_Perf_Change)\n",
		pkg, msr,
		((msr) & 0x4) ? "" : "No-",
		((msr) & 0x1) ? "" : "No-");

	return 0;
}