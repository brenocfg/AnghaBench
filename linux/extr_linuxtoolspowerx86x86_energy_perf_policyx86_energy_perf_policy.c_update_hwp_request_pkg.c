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
struct msr_hwp_request {int /*<<< orphan*/  hwp_epp; int /*<<< orphan*/  hwp_window; int /*<<< orphan*/  hwp_desired; int /*<<< orphan*/  hwp_max; int /*<<< orphan*/  hwp_min; } ;
struct msr_hwp_cap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hwp_epp; int /*<<< orphan*/  hwp_window; int /*<<< orphan*/  hwp_desired; int /*<<< orphan*/  hwp_max; int /*<<< orphan*/  hwp_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_HWP_CAPABILITIES ; 
 int MSR_HWP_REQUEST_PKG ; 
 int /*<<< orphan*/  check_hwp_request_v_hwp_capabilities (int,struct msr_hwp_request*,struct msr_hwp_cap*) ; 
 scalar_t__ debug ; 
 int* first_cpu_in_pkg ; 
 int /*<<< orphan*/  force ; 
 int /*<<< orphan*/  print_hwp_cap (int,struct msr_hwp_cap*,char*) ; 
 int /*<<< orphan*/  print_hwp_request_pkg (int,struct msr_hwp_request*,char*) ; 
 int /*<<< orphan*/  read_hwp_cap (int,struct msr_hwp_cap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_hwp_request (int,struct msr_hwp_request*,int) ; 
 TYPE_1__ req_update ; 
 scalar_t__ update_hwp_desired ; 
 scalar_t__ update_hwp_epp ; 
 scalar_t__ update_hwp_max ; 
 scalar_t__ update_hwp_min ; 
 scalar_t__ update_hwp_window ; 
 int /*<<< orphan*/  verify_hwp_req_self_consistency (int,struct msr_hwp_request*) ; 
 int /*<<< orphan*/  write_hwp_request (int,struct msr_hwp_request*,int) ; 

int update_hwp_request_pkg(int pkg)
{
	struct msr_hwp_request req;
	struct msr_hwp_cap cap;
	int cpu = first_cpu_in_pkg[pkg];

	int msr_offset = MSR_HWP_REQUEST_PKG;

	read_hwp_request(cpu, &req, msr_offset);
	if (debug)
		print_hwp_request_pkg(pkg, &req, "old: ");

	if (update_hwp_min)
		req.hwp_min = req_update.hwp_min;

	if (update_hwp_max)
		req.hwp_max = req_update.hwp_max;

	if (update_hwp_desired)
		req.hwp_desired = req_update.hwp_desired;

	if (update_hwp_window)
		req.hwp_window = req_update.hwp_window;

	if (update_hwp_epp)
		req.hwp_epp = req_update.hwp_epp;

	read_hwp_cap(cpu, &cap, MSR_HWP_CAPABILITIES);
	if (debug)
		print_hwp_cap(cpu, &cap, "");

	if (!force)
		check_hwp_request_v_hwp_capabilities(cpu, &req, &cap);

	verify_hwp_req_self_consistency(cpu, &req);

	write_hwp_request(cpu, &req, msr_offset);

	if (debug) {
		read_hwp_request(cpu, &req, msr_offset);
		print_hwp_request_pkg(pkg, &req, "new: ");
	}
	return 0;
}