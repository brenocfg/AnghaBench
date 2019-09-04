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
typedef  int u16 ;
struct brcms_phy {TYPE_3__* d11core; TYPE_1__* sh; } ;
struct TYPE_6__ {TYPE_2__* bus; } ;
struct TYPE_5__ {int /*<<< orphan*/  drv_cc; } ;
struct TYPE_4__ {scalar_t__ chip; int boardflags; int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 scalar_t__ BCMA_CHIP_ID_BCM4313 ; 
 int BFL_FEM ; 
 int /*<<< orphan*/  bcma_chipco_gpio_control (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  bcma_chipco_gpio_out (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  bcma_chipco_gpio_outen (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int wlapi_bmac_get_txant (int /*<<< orphan*/ ) ; 

void wlc_lcnphy_epa_switch(struct brcms_phy *pi, bool mode)
{
	if ((pi->sh->chip == BCMA_CHIP_ID_BCM4313) &&
	    (pi->sh->boardflags & BFL_FEM)) {
		if (mode) {
			u16 txant = 0;
			txant = wlapi_bmac_get_txant(pi->sh->physhim);
			if (txant == 1) {
				mod_phy_reg(pi, 0x44d, (0x1 << 2), (1) << 2);

				mod_phy_reg(pi, 0x44c, (0x1 << 2), (1) << 2);

			}

			bcma_chipco_gpio_control(&pi->d11core->bus->drv_cc,
						 0x0, 0x0);
			bcma_chipco_gpio_out(&pi->d11core->bus->drv_cc,
					     ~0x40, 0x40);
			bcma_chipco_gpio_outen(&pi->d11core->bus->drv_cc,
					       ~0x40, 0x40);
		} else {
			mod_phy_reg(pi, 0x44c, (0x1 << 2), (0) << 2);

			mod_phy_reg(pi, 0x44d, (0x1 << 2), (0) << 2);

			bcma_chipco_gpio_out(&pi->d11core->bus->drv_cc,
					     ~0x40, 0x00);
			bcma_chipco_gpio_outen(&pi->d11core->bus->drv_cc,
					       ~0x40, 0x00);
			bcma_chipco_gpio_control(&pi->d11core->bus->drv_cc,
						 0x0, 0x40);
		}
	}
}