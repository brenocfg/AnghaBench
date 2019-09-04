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
typedef  int u32 ;
struct TYPE_2__ {int ctl1; int ctl2; int /*<<< orphan*/  dw_cap_ptr; int /*<<< orphan*/  up_cap_ptr; } ;
struct pcie_link_state {int aspm_support; TYPE_1__ l1ss; int /*<<< orphan*/  downstream; int /*<<< orphan*/  pdev; } ;
struct aspm_register_info {int l1ss_cap; int /*<<< orphan*/  l1ss_cap_ptr; } ;

/* Variables and functions */
 int ASPM_STATE_L1_2_MASK ; 
 int PCI_L1SS_CAP_CM_RESTORE_TIME ; 
 int PCI_L1SS_CAP_P_PWR_ON_SCALE ; 
 int PCI_L1SS_CAP_P_PWR_ON_VALUE ; 
 scalar_t__ calc_l1ss_pwron (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  encode_l12_threshold (int,int*,int*) ; 
 int max (int,int) ; 

__attribute__((used)) static void aspm_calc_l1ss_info(struct pcie_link_state *link,
				struct aspm_register_info *upreg,
				struct aspm_register_info *dwreg)
{
	u32 val1, val2, scale1, scale2;
	u32 t_common_mode, t_power_on, l1_2_threshold, scale, value;

	link->l1ss.up_cap_ptr = upreg->l1ss_cap_ptr;
	link->l1ss.dw_cap_ptr = dwreg->l1ss_cap_ptr;
	link->l1ss.ctl1 = link->l1ss.ctl2 = 0;

	if (!(link->aspm_support & ASPM_STATE_L1_2_MASK))
		return;

	/* Choose the greater of the two Port Common_Mode_Restore_Times */
	val1 = (upreg->l1ss_cap & PCI_L1SS_CAP_CM_RESTORE_TIME) >> 8;
	val2 = (dwreg->l1ss_cap & PCI_L1SS_CAP_CM_RESTORE_TIME) >> 8;
	t_common_mode = max(val1, val2);

	/* Choose the greater of the two Port T_POWER_ON times */
	val1   = (upreg->l1ss_cap & PCI_L1SS_CAP_P_PWR_ON_VALUE) >> 19;
	scale1 = (upreg->l1ss_cap & PCI_L1SS_CAP_P_PWR_ON_SCALE) >> 16;
	val2   = (dwreg->l1ss_cap & PCI_L1SS_CAP_P_PWR_ON_VALUE) >> 19;
	scale2 = (dwreg->l1ss_cap & PCI_L1SS_CAP_P_PWR_ON_SCALE) >> 16;

	if (calc_l1ss_pwron(link->pdev, scale1, val1) >
	    calc_l1ss_pwron(link->downstream, scale2, val2)) {
		link->l1ss.ctl2 |= scale1 | (val1 << 3);
		t_power_on = calc_l1ss_pwron(link->pdev, scale1, val1);
	} else {
		link->l1ss.ctl2 |= scale2 | (val2 << 3);
		t_power_on = calc_l1ss_pwron(link->downstream, scale2, val2);
	}

	/*
	 * Set LTR_L1.2_THRESHOLD to the time required to transition the
	 * Link from L0 to L1.2 and back to L0 so we enter L1.2 only if
	 * downstream devices report (via LTR) that they can tolerate at
	 * least that much latency.
	 *
	 * Based on PCIe r3.1, sec 5.5.3.3.1, Figures 5-16 and 5-17, and
	 * Table 5-11.  T(POWER_OFF) is at most 2us and T(L1.2) is at
	 * least 4us.
	 */
	l1_2_threshold = 2 + 4 + t_common_mode + t_power_on;
	encode_l12_threshold(l1_2_threshold, &scale, &value);
	link->l1ss.ctl1 |= t_common_mode << 8 | scale << 29 | value << 16;
}