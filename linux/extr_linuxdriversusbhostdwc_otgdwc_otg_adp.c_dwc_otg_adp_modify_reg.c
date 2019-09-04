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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  dwc_otg_core_if_t ;

/* Variables and functions */
 int dwc_otg_adp_read_reg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_adp_write_reg (int /*<<< orphan*/ *,int) ; 

void dwc_otg_adp_modify_reg(dwc_otg_core_if_t * core_if, uint32_t clr,
			    uint32_t set)
{
	dwc_otg_adp_write_reg(core_if,
			      (dwc_otg_adp_read_reg(core_if) & (~clr)) | set);
}