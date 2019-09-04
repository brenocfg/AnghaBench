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
typedef  size_t u16 ;
struct spmi_pmic_arb {size_t* ppid_to_apid; } ;

/* Variables and functions */
 int ENODEV ; 
 size_t PMIC_ARB_APID_VALID ; 
 size_t pmic_arb_find_apid (struct spmi_pmic_arb*,size_t) ; 

__attribute__((used)) static int pmic_arb_ppid_to_apid_v2(struct spmi_pmic_arb *pmic_arb, u16 ppid)
{
	u16 apid_valid;

	apid_valid = pmic_arb->ppid_to_apid[ppid];
	if (!(apid_valid & PMIC_ARB_APID_VALID))
		apid_valid = pmic_arb_find_apid(pmic_arb, ppid);
	if (!(apid_valid & PMIC_ARB_APID_VALID))
		return -ENODEV;

	return apid_valid & ~PMIC_ARB_APID_VALID;
}