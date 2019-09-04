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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int CLK312_EN_LBN ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  PCS_TEST_SELECT_REG ; 
 int PMA_PMA_LED_ACTIVITY_LBN ; 
 int /*<<< orphan*/  PMA_PMD_LED_CTRL_REG ; 
 int /*<<< orphan*/  PMA_PMD_LED_OVERR_REG ; 
 int SFX7101_PMA_PMD_LED_DEFAULT ; 
 int /*<<< orphan*/  ef4_mdio_set_flag (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ef4_mdio_write (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tenxpress_init(struct ef4_nic *efx)
{
	/* Enable 312.5 MHz clock */
	ef4_mdio_write(efx, MDIO_MMD_PCS, PCS_TEST_SELECT_REG,
		       1 << CLK312_EN_LBN);

	/* Set the LEDs up as: Green = Link, Amber = Link/Act, Red = Off */
	ef4_mdio_set_flag(efx, MDIO_MMD_PMAPMD, PMA_PMD_LED_CTRL_REG,
			  1 << PMA_PMA_LED_ACTIVITY_LBN, true);
	ef4_mdio_write(efx, MDIO_MMD_PMAPMD, PMA_PMD_LED_OVERR_REG,
		       SFX7101_PMA_PMD_LED_DEFAULT);

	return 0;
}