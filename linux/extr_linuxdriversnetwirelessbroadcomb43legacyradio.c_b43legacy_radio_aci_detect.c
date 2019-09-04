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
typedef  int u8 ;
typedef  int u16 ;
struct b43legacy_phy {scalar_t__ aci_hw_rssi; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;

/* Variables and functions */
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_radio_selectchannel (struct b43legacy_wldev*,int,int /*<<< orphan*/ ) ; 

u8 b43legacy_radio_aci_detect(struct b43legacy_wldev *dev, u8 channel)
{
	struct b43legacy_phy *phy = &dev->phy;
	u8 ret = 0;
	u16 saved;
	u16 rssi;
	u16 temp;
	int i;
	int j = 0;

	saved = b43legacy_phy_read(dev, 0x0403);
	b43legacy_radio_selectchannel(dev, channel, 0);
	b43legacy_phy_write(dev, 0x0403, (saved & 0xFFF8) | 5);
	if (phy->aci_hw_rssi)
		rssi = b43legacy_phy_read(dev, 0x048A) & 0x3F;
	else
		rssi = saved & 0x3F;
	/* clamp temp to signed 5bit */
	if (rssi > 32)
		rssi -= 64;
	for (i = 0; i < 100; i++) {
		temp = (b43legacy_phy_read(dev, 0x047F) >> 8) & 0x3F;
		if (temp > 32)
			temp -= 64;
		if (temp < rssi)
			j++;
		if (j >= 20)
			ret = 1;
	}
	b43legacy_phy_write(dev, 0x0403, saved);

	return ret;
}