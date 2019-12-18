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
typedef  int u32 ;

/* Variables and functions */
 int CNTHCTL_EL1PCEN ; 
 int CNTHCTL_EL1PCTEN ; 
 int /*<<< orphan*/  cnthctl_el2 ; 
 int read_sysreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sysreg (int,int /*<<< orphan*/ ) ; 

void kvm_timer_init_vhe(void)
{
	/* When HCR_EL2.E2H ==1, EL1PCEN and EL1PCTEN are shifted by 10 */
	u32 cnthctl_shift = 10;
	u64 val;

	/*
	 * VHE systems allow the guest direct access to the EL1 physical
	 * timer/counter.
	 */
	val = read_sysreg(cnthctl_el2);
	val |= (CNTHCTL_EL1PCEN << cnthctl_shift);
	val |= (CNTHCTL_EL1PCTEN << cnthctl_shift);
	write_sysreg(val, cnthctl_el2);
}