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
 int /*<<< orphan*/  PLLCTL ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*) ; 
 unsigned int hw_read_20kx (struct hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_write_20kx (struct hw*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int hw_pll_init(struct hw *hw, unsigned int rsr)
{
	unsigned int pllctl;
	int i;

	pllctl = (48000 == rsr) ? 0x1480a001 : 0x1480a731;
	for (i = 0; i < 3; i++) {
		if (hw_read_20kx(hw, PLLCTL) == pllctl)
			break;

		hw_write_20kx(hw, PLLCTL, pllctl);
		msleep(40);
	}
	if (i >= 3) {
		dev_alert(hw->card->dev, "PLL initialization failed!!!\n");
		return -EBUSY;
	}

	return 0;
}