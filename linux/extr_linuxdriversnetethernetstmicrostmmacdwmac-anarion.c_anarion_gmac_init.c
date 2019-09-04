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
struct platform_device {int dummy; } ;
struct anarion_gmac {int phy_intf_sel; } ;

/* Variables and functions */
 int GMAC_CONFIG_INTF_SEL_MASK ; 
 int /*<<< orphan*/  GMAC_RESET_CONTROL_REG ; 
 int /*<<< orphan*/  GMAC_SW_CONFIG_REG ; 
 int gmac_read_reg (struct anarion_gmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmac_write_reg (struct anarion_gmac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int anarion_gmac_init(struct platform_device *pdev, void *priv)
{
	uint32_t sw_config;
	struct anarion_gmac *gmac = priv;

	/* Reset logic, configure interface mode, then release reset. SIMPLE! */
	gmac_write_reg(gmac, GMAC_RESET_CONTROL_REG, 1);

	sw_config = gmac_read_reg(gmac, GMAC_SW_CONFIG_REG);
	sw_config &= ~GMAC_CONFIG_INTF_SEL_MASK;
	sw_config |= (gmac->phy_intf_sel & GMAC_CONFIG_INTF_SEL_MASK);
	gmac_write_reg(gmac, GMAC_SW_CONFIG_REG, sw_config);

	gmac_write_reg(gmac, GMAC_RESET_CONTROL_REG, 0);

	return 0;
}