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
typedef  int u64 ;
struct perf_output_handle {int dummy; } ;
typedef  enum arm_spe_pmu_buf_fault_action { ____Placeholder_arm_spe_pmu_buf_fault_action } arm_spe_pmu_buf_fault_action ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int PERF_AUX_FLAG_COLLISION ; 
 int PERF_AUX_FLAG_PARTIAL ; 
 int PERF_AUX_FLAG_TRUNCATED ; 
 int SPE_PMU_BUF_FAULT_ACT_FATAL ; 
 int SPE_PMU_BUF_FAULT_ACT_OK ; 
 int SPE_PMU_BUF_FAULT_ACT_SPURIOUS ; 
 int /*<<< orphan*/  SYS_PMBLIMITR_EL1 ; 
 int /*<<< orphan*/  SYS_PMBPTR_EL1 ; 
 int /*<<< orphan*/  SYS_PMBSR_EL1 ; 
#define  SYS_PMBSR_EL1_BUF_BSC_FULL 131 
 int SYS_PMBSR_EL1_BUF_BSC_MASK ; 
 int SYS_PMBSR_EL1_BUF_BSC_SHIFT ; 
 int /*<<< orphan*/  SYS_PMBSR_EL1_COLL_SHIFT ; 
 int /*<<< orphan*/  SYS_PMBSR_EL1_DL_SHIFT ; 
#define  SYS_PMBSR_EL1_EC_BUF 130 
#define  SYS_PMBSR_EL1_EC_FAULT_S1 129 
#define  SYS_PMBSR_EL1_EC_FAULT_S2 128 
 int SYS_PMBSR_EL1_EC_MASK ; 
 int SYS_PMBSR_EL1_EC_SHIFT ; 
 int /*<<< orphan*/  SYS_PMBSR_EL1_S_SHIFT ; 
 int /*<<< orphan*/  arm_spe_perf_aux_output_end (struct perf_output_handle*) ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  nsh ; 
 int /*<<< orphan*/  perf_aux_output_flag (struct perf_output_handle*,int) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,char const*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  psb_csync () ; 
 int read_sysreg_s (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static enum arm_spe_pmu_buf_fault_action
arm_spe_pmu_buf_get_fault_act(struct perf_output_handle *handle)
{
	const char *err_str;
	u64 pmbsr;
	enum arm_spe_pmu_buf_fault_action ret;

	/*
	 * Ensure new profiling data is visible to the CPU and any external
	 * aborts have been resolved.
	 */
	psb_csync();
	dsb(nsh);

	/* Ensure hardware updates to PMBPTR_EL1 are visible */
	isb();

	/* Service required? */
	pmbsr = read_sysreg_s(SYS_PMBSR_EL1);
	if (!(pmbsr & BIT(SYS_PMBSR_EL1_S_SHIFT)))
		return SPE_PMU_BUF_FAULT_ACT_SPURIOUS;

	/*
	 * If we've lost data, disable profiling and also set the PARTIAL
	 * flag to indicate that the last record is corrupted.
	 */
	if (pmbsr & BIT(SYS_PMBSR_EL1_DL_SHIFT))
		perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED |
					     PERF_AUX_FLAG_PARTIAL);

	/* Report collisions to userspace so that it can up the period */
	if (pmbsr & BIT(SYS_PMBSR_EL1_COLL_SHIFT))
		perf_aux_output_flag(handle, PERF_AUX_FLAG_COLLISION);

	/* We only expect buffer management events */
	switch (pmbsr & (SYS_PMBSR_EL1_EC_MASK << SYS_PMBSR_EL1_EC_SHIFT)) {
	case SYS_PMBSR_EL1_EC_BUF:
		/* Handled below */
		break;
	case SYS_PMBSR_EL1_EC_FAULT_S1:
	case SYS_PMBSR_EL1_EC_FAULT_S2:
		err_str = "Unexpected buffer fault";
		goto out_err;
	default:
		err_str = "Unknown error code";
		goto out_err;
	}

	/* Buffer management event */
	switch (pmbsr &
		(SYS_PMBSR_EL1_BUF_BSC_MASK << SYS_PMBSR_EL1_BUF_BSC_SHIFT)) {
	case SYS_PMBSR_EL1_BUF_BSC_FULL:
		ret = SPE_PMU_BUF_FAULT_ACT_OK;
		goto out_stop;
	default:
		err_str = "Unknown buffer status code";
	}

out_err:
	pr_err_ratelimited("%s on CPU %d [PMBSR=0x%016llx, PMBPTR=0x%016llx, PMBLIMITR=0x%016llx]\n",
			   err_str, smp_processor_id(), pmbsr,
			   read_sysreg_s(SYS_PMBPTR_EL1),
			   read_sysreg_s(SYS_PMBLIMITR_EL1));
	ret = SPE_PMU_BUF_FAULT_ACT_FATAL;

out_stop:
	arm_spe_perf_aux_output_end(handle);
	return ret;
}