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
struct hw {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PLLCTL_B ; 
 int /*<<< orphan*/  PLLCTL_FD ; 
 int /*<<< orphan*/  PLLCTL_RD ; 
 int /*<<< orphan*/  PLLCTL_SRC ; 
 int /*<<< orphan*/  PLLSTAT_B ; 
 int /*<<< orphan*/  PLLSTAT_CCS ; 
 int /*<<< orphan*/  PLLSTAT_CFD ; 
 int /*<<< orphan*/  PLLSTAT_CRD ; 
 int /*<<< orphan*/  PLLSTAT_PD ; 
 int /*<<< orphan*/  PLL_CTL ; 
 int /*<<< orphan*/  PLL_ENB ; 
 int /*<<< orphan*/  PLL_STAT ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ get_field (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  set_field (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hw_pll_init(struct hw *hw, unsigned int rsr)
{
	unsigned int pllenb;
	unsigned int pllctl;
	unsigned int pllstat;
	int i;

	pllenb = 0xB;
	hw_write_20kx(hw, PLL_ENB, pllenb);
	pllctl = 0x20C00000;
	set_field(&pllctl, PLLCTL_B, 0);
	set_field(&pllctl, PLLCTL_FD, 48000 == rsr ? 16 - 4 : 147 - 4);
	set_field(&pllctl, PLLCTL_RD, 48000 == rsr ? 1 - 1 : 10 - 1);
	hw_write_20kx(hw, PLL_CTL, pllctl);
	msleep(40);

	pllctl = hw_read_20kx(hw, PLL_CTL);
	set_field(&pllctl, PLLCTL_FD, 48000 == rsr ? 16 - 2 : 147 - 2);
	hw_write_20kx(hw, PLL_CTL, pllctl);
	msleep(40);

	for (i = 0; i < 1000; i++) {
		pllstat = hw_read_20kx(hw, PLL_STAT);
		if (get_field(pllstat, PLLSTAT_PD))
			continue;

		if (get_field(pllstat, PLLSTAT_B) !=
					get_field(pllctl, PLLCTL_B))
			continue;

		if (get_field(pllstat, PLLSTAT_CCS) !=
					get_field(pllctl, PLLCTL_SRC))
			continue;

		if (get_field(pllstat, PLLSTAT_CRD) !=
					get_field(pllctl, PLLCTL_RD))
			continue;

		if (get_field(pllstat, PLLSTAT_CFD) !=
					get_field(pllctl, PLLCTL_FD))
			continue;

		break;
	}
	if (i >= 1000) {
		dev_alert(hw->card->dev,
			  "PLL initialization failed!!!\n");
		return -EBUSY;
	}

	return 0;
}