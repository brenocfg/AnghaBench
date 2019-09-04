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
struct TYPE_2__ {scalar_t__ do_full_init; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R2057_RFPLL_MASTER ; 
 int /*<<< orphan*/  R2057_RFPLL_MISC_CAL_RESETN ; 
 int /*<<< orphan*/  R2057_XTALPUOVR_PINCTRL ; 
 int /*<<< orphan*/  R2057_XTAL_CONFIG2 ; 
 int /*<<< orphan*/  b43_radio_2057_rcal (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_2057_rccal (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void b43_radio_2057_init_post(struct b43_wldev *dev)
{
	b43_radio_set(dev, R2057_XTALPUOVR_PINCTRL, 0x1);

	if (0) /* FIXME: Is this BCM43217 specific? */
		b43_radio_set(dev, R2057_XTALPUOVR_PINCTRL, 0x2);

	b43_radio_set(dev, R2057_RFPLL_MISC_CAL_RESETN, 0x78);
	b43_radio_set(dev, R2057_XTAL_CONFIG2, 0x80);
	usleep_range(2000, 3000);
	b43_radio_mask(dev, R2057_RFPLL_MISC_CAL_RESETN, ~0x78);
	b43_radio_mask(dev, R2057_XTAL_CONFIG2, ~0x80);

	if (dev->phy.do_full_init) {
		b43_radio_2057_rcal(dev);
		b43_radio_2057_rccal(dev);
	}
	b43_radio_mask(dev, R2057_RFPLL_MASTER, ~0x8);
}