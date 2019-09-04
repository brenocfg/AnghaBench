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
typedef  enum ef4_led_mode { ____Placeholder_ef4_led_mode } ef4_led_mode ;

/* Variables and functions */
#define  EF4_LED_OFF 129 
#define  EF4_LED_ON 128 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int PMA_PMD_LED_LINK_LBN ; 
 int PMA_PMD_LED_OFF ; 
 int PMA_PMD_LED_ON ; 
 int /*<<< orphan*/  PMA_PMD_LED_OVERR_REG ; 
 int PMA_PMD_LED_RX_LBN ; 
 int PMA_PMD_LED_TX_LBN ; 
 int SFX7101_PMA_PMD_LED_DEFAULT ; 
 int /*<<< orphan*/  ef4_mdio_write (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void tenxpress_set_id_led(struct ef4_nic *efx, enum ef4_led_mode mode)
{
	int reg;

	switch (mode) {
	case EF4_LED_OFF:
		reg = (PMA_PMD_LED_OFF << PMA_PMD_LED_TX_LBN) |
			(PMA_PMD_LED_OFF << PMA_PMD_LED_RX_LBN) |
			(PMA_PMD_LED_OFF << PMA_PMD_LED_LINK_LBN);
		break;
	case EF4_LED_ON:
		reg = (PMA_PMD_LED_ON << PMA_PMD_LED_TX_LBN) |
			(PMA_PMD_LED_ON << PMA_PMD_LED_RX_LBN) |
			(PMA_PMD_LED_ON << PMA_PMD_LED_LINK_LBN);
		break;
	default:
		reg = SFX7101_PMA_PMD_LED_DEFAULT;
		break;
	}

	ef4_mdio_write(efx, MDIO_MMD_PMAPMD, PMA_PMD_LED_OVERR_REG, reg);
}