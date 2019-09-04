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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2063_PLL_JTAG_CALNRST ; 
 int /*<<< orphan*/  B2063_PLL_SP1 ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int b43_radio_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void lpphy_b2063_vco_calib(struct b43_wldev *dev)
{
	u16 tmp;

	b43_radio_mask(dev, B2063_PLL_SP1, ~0x40);
	tmp = b43_radio_read(dev, B2063_PLL_JTAG_CALNRST) & 0xF8;
	b43_radio_write(dev, B2063_PLL_JTAG_CALNRST, tmp);
	udelay(1);
	b43_radio_write(dev, B2063_PLL_JTAG_CALNRST, tmp | 0x4);
	udelay(1);
	b43_radio_write(dev, B2063_PLL_JTAG_CALNRST, tmp | 0x6);
	udelay(1);
	b43_radio_write(dev, B2063_PLL_JTAG_CALNRST, tmp | 0x7);
	udelay(300);
	b43_radio_set(dev, B2063_PLL_SP1, 0x40);
}