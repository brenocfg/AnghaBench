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
 int /*<<< orphan*/  B2056_SYN_COM_CTRL ; 
 int /*<<< orphan*/  B2056_SYN_COM_PU ; 
 int /*<<< orphan*/  B2056_SYN_COM_RESET ; 
 int /*<<< orphan*/  B2056_SYN_PLL_MAST2 ; 
 int /*<<< orphan*/  B2056_SYN_RCCAL_CTRL0 ; 
 int /*<<< orphan*/  b43_radio_2056_rcal (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void b43_radio_init2056_post(struct b43_wldev *dev)
{
	b43_radio_set(dev, B2056_SYN_COM_CTRL, 0xB);
	b43_radio_set(dev, B2056_SYN_COM_PU, 0x2);
	b43_radio_set(dev, B2056_SYN_COM_RESET, 0x2);
	msleep(1);
	b43_radio_mask(dev, B2056_SYN_COM_RESET, ~0x2);
	b43_radio_mask(dev, B2056_SYN_PLL_MAST2, ~0xFC);
	b43_radio_mask(dev, B2056_SYN_RCCAL_CTRL0, ~0x1);
	if (dev->phy.do_full_init)
		b43_radio_2056_rcal(dev);
}