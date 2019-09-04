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
struct lcn_tx_gains {int gm_gain; int pga_gain; int pad_gain; int /*<<< orphan*/  dac_gain; } ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int b43_phy_lcn_get_pa_gain (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_lcn_set_dac_gain (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_lcn_set_tx_gain_override (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_phy_lcn_set_tx_gain(struct b43_wldev *dev,
				    struct lcn_tx_gains *target_gains)
{
	u16 pa_gain = b43_phy_lcn_get_pa_gain(dev);

	b43_phy_write(dev, 0x4b5,
		      (target_gains->gm_gain | (target_gains->pga_gain << 8)));
	b43_phy_maskset(dev, 0x4fb, ~0x7fff,
			(target_gains->pad_gain | (pa_gain << 8)));
	b43_phy_write(dev, 0x4fc,
		      (target_gains->gm_gain | (target_gains->pga_gain << 8)));
	b43_phy_maskset(dev, 0x4fd, ~0x7fff,
			(target_gains->pad_gain | (pa_gain << 8)));

	b43_phy_lcn_set_dac_gain(dev, target_gains->dac_gain);
	b43_phy_lcn_set_tx_gain_override(dev, true);
}