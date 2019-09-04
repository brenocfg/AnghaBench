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
struct usb_phy {int dummy; } ;
struct isp1301 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP1301_I2C_INTERRUPT_FALLING ; 
 int /*<<< orphan*/  ISP1301_I2C_INTERRUPT_LATCH ; 
 int /*<<< orphan*/  ISP1301_I2C_INTERRUPT_RISING ; 
 int /*<<< orphan*/  ISP1301_I2C_MODE_CONTROL_1 ; 
 int /*<<< orphan*/  ISP1301_I2C_MODE_CONTROL_2 ; 
 int /*<<< orphan*/  ISP1301_I2C_OTG_CONTROL_1 ; 
 int MC1_DAT_SE0 ; 
 int MC1_SPEED_REG ; 
 int MC1_UART_EN ; 
 int MC2_BI_DI ; 
 int MC2_PSW_EN ; 
 int MC2_SPD_SUSP_CTRL ; 
 int OTG1_DM_PULLDOWN ; 
 int OTG1_DM_PULLUP ; 
 int OTG1_DP_PULLDOWN ; 
 int OTG1_DP_PULLUP ; 
 int /*<<< orphan*/  isp1301_clear (struct isp1301*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isp1301_write (struct isp1301*,int /*<<< orphan*/ ,int) ; 
 struct isp1301* phy_to_isp (struct usb_phy*) ; 

__attribute__((used)) static int isp1301_phy_init(struct usb_phy *phy)
{
	struct isp1301 *isp = phy_to_isp(phy);

	/* Disable transparent UART mode first */
	isp1301_clear(isp, ISP1301_I2C_MODE_CONTROL_1, MC1_UART_EN);
	isp1301_clear(isp, ISP1301_I2C_MODE_CONTROL_1, ~MC1_SPEED_REG);
	isp1301_write(isp, ISP1301_I2C_MODE_CONTROL_1, MC1_SPEED_REG);
	isp1301_clear(isp, ISP1301_I2C_MODE_CONTROL_2, ~0);
	isp1301_write(isp, ISP1301_I2C_MODE_CONTROL_2, (MC2_BI_DI | MC2_PSW_EN
				| MC2_SPD_SUSP_CTRL));

	isp1301_clear(isp, ISP1301_I2C_OTG_CONTROL_1, ~0);
	isp1301_write(isp, ISP1301_I2C_MODE_CONTROL_1, MC1_DAT_SE0);
	isp1301_write(isp, ISP1301_I2C_OTG_CONTROL_1, (OTG1_DM_PULLDOWN
				| OTG1_DP_PULLDOWN));
	isp1301_clear(isp, ISP1301_I2C_OTG_CONTROL_1, (OTG1_DM_PULLUP
				| OTG1_DP_PULLUP));

	/* mask all interrupts */
	isp1301_clear(isp, ISP1301_I2C_INTERRUPT_LATCH, ~0);
	isp1301_clear(isp, ISP1301_I2C_INTERRUPT_FALLING, ~0);
	isp1301_clear(isp, ISP1301_I2C_INTERRUPT_RISING, ~0);

	return 0;
}