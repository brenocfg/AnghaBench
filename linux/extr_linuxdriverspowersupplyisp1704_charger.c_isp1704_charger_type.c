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
typedef  int u8 ;
struct isp1704_charger {int dummy; } ;

/* Variables and functions */
 int POWER_SUPPLY_TYPE_USB_CDP ; 
 int POWER_SUPPLY_TYPE_USB_DCP ; 
 int /*<<< orphan*/  ULPI_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULPI_DEBUG ; 
 int /*<<< orphan*/  ULPI_FUNC_CTRL ; 
 int ULPI_FUNC_CTRL_FULL_SPEED ; 
 int ULPI_FUNC_CTRL_RESET ; 
 int ULPI_FUNC_CTRL_TERMSELECT ; 
 int ULPI_FUNC_CTRL_XCVRSEL_MASK ; 
 int /*<<< orphan*/  ULPI_OTG_CTRL ; 
 int ULPI_OTG_CTRL_DM_PULLDOWN ; 
 int ULPI_OTG_CTRL_DP_PULLDOWN ; 
 int /*<<< orphan*/  ULPI_SET (int /*<<< orphan*/ ) ; 
 int isp1704_read (struct isp1704_charger*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1704_write (struct isp1704_charger*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline int isp1704_charger_type(struct isp1704_charger *isp)
{
	u8 reg;
	u8 func_ctrl;
	u8 otg_ctrl;
	int type = POWER_SUPPLY_TYPE_USB_DCP;

	func_ctrl = isp1704_read(isp, ULPI_FUNC_CTRL);
	otg_ctrl = isp1704_read(isp, ULPI_OTG_CTRL);

	/* disable pulldowns */
	reg = ULPI_OTG_CTRL_DM_PULLDOWN | ULPI_OTG_CTRL_DP_PULLDOWN;
	isp1704_write(isp, ULPI_CLR(ULPI_OTG_CTRL), reg);

	/* full speed */
	isp1704_write(isp, ULPI_CLR(ULPI_FUNC_CTRL),
			ULPI_FUNC_CTRL_XCVRSEL_MASK);
	isp1704_write(isp, ULPI_SET(ULPI_FUNC_CTRL),
			ULPI_FUNC_CTRL_FULL_SPEED);

	/* Enable strong pull-up on DP (1.5K) and reset */
	reg = ULPI_FUNC_CTRL_TERMSELECT | ULPI_FUNC_CTRL_RESET;
	isp1704_write(isp, ULPI_SET(ULPI_FUNC_CTRL), reg);
	usleep_range(1000, 2000);

	reg = isp1704_read(isp, ULPI_DEBUG);
	if ((reg & 3) != 3)
		type = POWER_SUPPLY_TYPE_USB_CDP;

	/* recover original state */
	isp1704_write(isp, ULPI_FUNC_CTRL, func_ctrl);
	isp1704_write(isp, ULPI_OTG_CTRL, otg_ctrl);

	return type;
}