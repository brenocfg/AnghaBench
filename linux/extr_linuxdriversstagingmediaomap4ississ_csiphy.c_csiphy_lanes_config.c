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
typedef  int u32 ;
struct TYPE_5__ {int pos; scalar_t__ pol; } ;
struct TYPE_6__ {TYPE_2__ clk; TYPE_1__* data; } ;
struct iss_csiphy {unsigned int max_data_lanes; int /*<<< orphan*/  cfg_regs; int /*<<< orphan*/  iss; TYPE_3__ lanes; } ;
struct TYPE_4__ {int pos; scalar_t__ pol; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_COMPLEXIO_CFG ; 
 int CSI2_COMPLEXIO_CFG_CLOCK_POL ; 
 int CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK ; 
 int CSI2_COMPLEXIO_CFG_CLOCK_POSITION_SHIFT ; 
 int CSI2_COMPLEXIO_CFG_DATA_POL (unsigned int) ; 
 int CSI2_COMPLEXIO_CFG_DATA_POSITION_MASK (unsigned int) ; 
 int CSI2_COMPLEXIO_CFG_DATA_POSITION_SHIFT (unsigned int) ; 
 int iss_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void csiphy_lanes_config(struct iss_csiphy *phy)
{
	unsigned int i;
	u32 reg;

	reg = iss_reg_read(phy->iss, phy->cfg_regs, CSI2_COMPLEXIO_CFG);

	for (i = 0; i < phy->max_data_lanes; i++) {
		reg &= ~(CSI2_COMPLEXIO_CFG_DATA_POL(i + 1) |
			 CSI2_COMPLEXIO_CFG_DATA_POSITION_MASK(i + 1));
		reg |= (phy->lanes.data[i].pol ?
			CSI2_COMPLEXIO_CFG_DATA_POL(i + 1) : 0);
		reg |= (phy->lanes.data[i].pos <<
			CSI2_COMPLEXIO_CFG_DATA_POSITION_SHIFT(i + 1));
	}

	reg &= ~(CSI2_COMPLEXIO_CFG_CLOCK_POL |
		 CSI2_COMPLEXIO_CFG_CLOCK_POSITION_MASK);
	reg |= phy->lanes.clk.pol ? CSI2_COMPLEXIO_CFG_CLOCK_POL : 0;
	reg |= phy->lanes.clk.pos << CSI2_COMPLEXIO_CFG_CLOCK_POSITION_SHIFT;

	iss_reg_write(phy->iss, phy->cfg_regs, CSI2_COMPLEXIO_CFG, reg);
}