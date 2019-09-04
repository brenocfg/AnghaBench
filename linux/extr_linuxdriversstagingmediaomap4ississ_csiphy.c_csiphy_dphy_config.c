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
struct TYPE_2__ {int ths_term; int ths_settle; int tclk_term; int tclk_miss; int tclk_settle; } ;
struct iss_csiphy {int /*<<< orphan*/  phy_regs; int /*<<< orphan*/  iss; TYPE_1__ dphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REGISTER0 ; 
 int REGISTER0_THS_SETTLE_SHIFT ; 
 int REGISTER0_THS_TERM_SHIFT ; 
 int /*<<< orphan*/  REGISTER1 ; 
 int REGISTER1_CTRLCLK_DIV_FACTOR_SHIFT ; 
 int REGISTER1_DPHY_HS_SYNC_PATTERN_SHIFT ; 
 int REGISTER1_TCLK_SETTLE_SHIFT ; 
 int REGISTER1_TCLK_TERM_SHIFT ; 
 int /*<<< orphan*/  iss_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void csiphy_dphy_config(struct iss_csiphy *phy)
{
	u32 reg;

	/* Set up REGISTER0 */
	reg = phy->dphy.ths_term << REGISTER0_THS_TERM_SHIFT;
	reg |= phy->dphy.ths_settle << REGISTER0_THS_SETTLE_SHIFT;

	iss_reg_write(phy->iss, phy->phy_regs, REGISTER0, reg);

	/* Set up REGISTER1 */
	reg = phy->dphy.tclk_term << REGISTER1_TCLK_TERM_SHIFT;
	reg |= phy->dphy.tclk_miss << REGISTER1_CTRLCLK_DIV_FACTOR_SHIFT;
	reg |= phy->dphy.tclk_settle << REGISTER1_TCLK_SETTLE_SHIFT;
	reg |= 0xb8 << REGISTER1_DPHY_HS_SYNC_PATTERN_SHIFT;

	iss_reg_write(phy->iss, phy->phy_regs, REGISTER1, reg);
}