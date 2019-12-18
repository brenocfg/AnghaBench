#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ip17xx_state {TYPE_1__* regs; } ;
struct TYPE_5__ {int MODEL_NO; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 TYPE_1__ IP175A ; 
 TYPE_1__ IP175C ; 
 TYPE_1__ IP175D ; 
 TYPE_1__ IP178C ; 
 int ip_phy_read (struct ip17xx_state*,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_warning (char*,int,int) ; 

__attribute__((used)) static int get_model(struct ip17xx_state *state)
{
	int id1, id2;
	int oui_id, model_no, rev_no, chip_no;

	id1 = ip_phy_read(state, 0, 2);
	id2 = ip_phy_read(state, 0, 3);
	oui_id = (id1 << 6) | ((id2 >> 10) & 0x3f);
	model_no = (id2 >> 4) & 0x3f;
	rev_no = id2 & 0xf;
	pr_debug("IP17xx: Identified oui=%06x model=%02x rev=%X\n", oui_id, model_no, rev_no);

	if (oui_id != 0x0090c3)  // No other oui_id should have reached us anyway
		return -ENODEV;

	if (model_no == IP175A.MODEL_NO) {
		state->regs = &IP175A;
	} else if (model_no == IP175C.MODEL_NO) {
		/*
		 *  Several models share the same model_no:
		 *  178C has more PHYs, so we try whether the device responds to a read from PHY5
		 *  175D has a new chip ID register
		 *  175C has neither
		 */
		if (ip_phy_read(state, 5, 2) == 0x0243) {
			state->regs = &IP178C;
		} else {
			chip_no = ip_phy_read(state, 20, 0);
			pr_debug("IP17xx: Chip ID register reads %04x\n", chip_no);
			if (chip_no == 0x175d) {
				state->regs = &IP175D;
			} else {
				state->regs = &IP175C;
			}
		}
	} else {
		pr_warning("IP17xx: Found an unknown IC+ switch with model number %02x, revision %X.\n", model_no, rev_no);
		return -EPERM;
	}
	return 0;
}