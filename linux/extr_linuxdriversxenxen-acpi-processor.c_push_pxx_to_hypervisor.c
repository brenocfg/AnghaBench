#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xen_processor_px {int dummy; } ;
struct xen_processor_performance {int flags; int /*<<< orphan*/  states; int /*<<< orphan*/  status_register; int /*<<< orphan*/  control_register; int /*<<< orphan*/  platform_limit; } ;
struct TYPE_4__ {int id; struct xen_processor_performance perf; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ set_pminfo; } ;
struct xen_platform_op {TYPE_2__ u; int /*<<< orphan*/  interface_version; int /*<<< orphan*/  cmd; } ;
struct acpi_processor_performance {unsigned int state_count; unsigned int state; TYPE_3__* states; int /*<<< orphan*/  status_register; int /*<<< orphan*/  control_register; } ;
struct acpi_processor {int acpi_id; struct acpi_processor_performance* performance; int /*<<< orphan*/  performance_platform_limit; } ;
struct TYPE_6__ {scalar_t__ transition_latency; scalar_t__ power; scalar_t__ core_frequency; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOSYS ; 
 int HYPERVISOR_platform_op (struct xen_platform_op*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct xen_processor_px*) ; 
 int /*<<< orphan*/  XENPF_INTERFACE_VERSION ; 
 int /*<<< orphan*/  XENPF_set_processor_pminfo ; 
 int /*<<< orphan*/  XEN_PM_PX ; 
 int XEN_PX_PCT ; 
 int XEN_PX_PPC ; 
 int XEN_PX_PSD ; 
 int XEN_PX_PSS ; 
 int /*<<< orphan*/  kfree (struct xen_processor_px*) ; 
 int /*<<< orphan*/  no_hypercall ; 
 int /*<<< orphan*/  pr_debug (char*,char,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int /*<<< orphan*/  set_xen_guest_handle (int /*<<< orphan*/ ,struct xen_processor_px*) ; 
 int /*<<< orphan*/  xen_copy_pct_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xen_copy_psd_data (struct acpi_processor*,struct xen_processor_performance*) ; 
 struct xen_processor_px* xen_copy_pss_data (struct acpi_processor*,struct xen_processor_performance*) ; 

__attribute__((used)) static int push_pxx_to_hypervisor(struct acpi_processor *_pr)
{
	int ret = 0;
	struct xen_platform_op op = {
		.cmd			= XENPF_set_processor_pminfo,
		.interface_version	= XENPF_INTERFACE_VERSION,
		.u.set_pminfo.id	= _pr->acpi_id,
		.u.set_pminfo.type	= XEN_PM_PX,
	};
	struct xen_processor_performance *dst_perf;
	struct xen_processor_px *dst_states = NULL;

	dst_perf = &op.u.set_pminfo.perf;

	dst_perf->platform_limit = _pr->performance_platform_limit;
	dst_perf->flags |= XEN_PX_PPC;
	xen_copy_pct_data(&(_pr->performance->control_register),
			  &dst_perf->control_register);
	xen_copy_pct_data(&(_pr->performance->status_register),
			  &dst_perf->status_register);
	dst_perf->flags |= XEN_PX_PCT;
	dst_states = xen_copy_pss_data(_pr, dst_perf);
	if (!IS_ERR_OR_NULL(dst_states)) {
		set_xen_guest_handle(dst_perf->states, dst_states);
		dst_perf->flags |= XEN_PX_PSS;
	}
	if (!xen_copy_psd_data(_pr, dst_perf))
		dst_perf->flags |= XEN_PX_PSD;

	if (dst_perf->flags != (XEN_PX_PSD | XEN_PX_PSS | XEN_PX_PCT | XEN_PX_PPC)) {
		pr_warn("ACPI CPU%u missing some P-state data (%x), skipping\n",
			_pr->acpi_id, dst_perf->flags);
		ret = -ENODEV;
		goto err_free;
	}

	if (!no_hypercall)
		ret = HYPERVISOR_platform_op(&op);

	if (!ret) {
		struct acpi_processor_performance *perf;
		unsigned int i;

		perf = _pr->performance;
		pr_debug("ACPI CPU%u - P-states uploaded.\n", _pr->acpi_id);
		for (i = 0; i < perf->state_count; i++) {
			pr_debug("     %cP%d: %d MHz, %d mW, %d uS\n",
			(i == perf->state ? '*' : ' '), i,
			(u32) perf->states[i].core_frequency,
			(u32) perf->states[i].power,
			(u32) perf->states[i].transition_latency);
		}
	} else if ((ret != -EINVAL) && (ret != -ENOSYS))
		/* EINVAL means the ACPI ID is incorrect - meaning the ACPI
		 * table is referencing a non-existing CPU - which can happen
		 * with broken ACPI tables. */
		pr_warn("(_PXX): Hypervisor error (%d) for ACPI CPU%u\n",
			ret, _pr->acpi_id);
err_free:
	if (!IS_ERR_OR_NULL(dst_states))
		kfree(dst_states);

	return ret;
}