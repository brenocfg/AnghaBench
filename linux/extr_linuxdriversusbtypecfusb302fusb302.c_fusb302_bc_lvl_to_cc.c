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
typedef  scalar_t__ u8 ;
typedef  enum typec_cc_status { ____Placeholder_typec_cc_status } typec_cc_status ;

/* Variables and functions */
 scalar_t__ FUSB_REG_STATUS0_BC_LVL_1230_MAX ; 
 scalar_t__ FUSB_REG_STATUS0_BC_LVL_200_600 ; 
 scalar_t__ FUSB_REG_STATUS0_BC_LVL_600_1230 ; 
 int TYPEC_CC_OPEN ; 
 int TYPEC_CC_RP_1_5 ; 
 int TYPEC_CC_RP_3_0 ; 
 int TYPEC_CC_RP_DEF ; 

__attribute__((used)) static enum typec_cc_status fusb302_bc_lvl_to_cc(u8 bc_lvl)
{
	if (bc_lvl == FUSB_REG_STATUS0_BC_LVL_1230_MAX)
		return TYPEC_CC_RP_3_0;
	if (bc_lvl == FUSB_REG_STATUS0_BC_LVL_600_1230)
		return TYPEC_CC_RP_1_5;
	if (bc_lvl == FUSB_REG_STATUS0_BC_LVL_200_600)
		return TYPEC_CC_RP_DEF;
	return TYPEC_CC_OPEN;
}