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
 scalar_t__ APIC_BASE_MSR ; 
 int APIC_DEST_SELF ; 
 int APIC_DM_SMI ; 
 int APIC_ICR ; 
 int APIC_INT_ASSERT ; 
 int /*<<< orphan*/  wrmsr (scalar_t__,int) ; 

void self_smi(void)
{
	wrmsr(APIC_BASE_MSR + (APIC_ICR >> 4),
	      APIC_DEST_SELF | APIC_INT_ASSERT | APIC_DM_SMI);
}