#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct b43_phy {int radio_ver; int /*<<< orphan*/  type; struct b43_phy_g* g; } ;
struct b43_wldev {TYPE_2__* dev; struct b43_phy phy; } ;
struct b43_phy_g {int* nrssi_lt; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int s32 ;
struct TYPE_4__ {TYPE_1__* bus_sprom; } ;
struct TYPE_3__ {int boardflags_lo; } ;

/* Variables and functions */
 int B43_BFL_RSSI ; 
 int /*<<< orphan*/  B43_PHYTYPE_G ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 

__attribute__((used)) static s8 b43_rssi_postprocess(struct b43_wldev *dev,
			       u8 in_rssi, int ofdm,
			       int adjust_2053, int adjust_2050)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	s32 tmp;

	switch (phy->radio_ver) {
	case 0x2050:
		if (ofdm) {
			tmp = in_rssi;
			if (tmp > 127)
				tmp -= 256;
			tmp *= 73;
			tmp /= 64;
			if (adjust_2050)
				tmp += 25;
			else
				tmp -= 3;
		} else {
			if (dev->dev->bus_sprom->
			    boardflags_lo & B43_BFL_RSSI) {
				if (in_rssi > 63)
					in_rssi = 63;
				B43_WARN_ON(phy->type != B43_PHYTYPE_G);
				tmp = gphy->nrssi_lt[in_rssi];
				tmp = 31 - tmp;
				tmp *= -131;
				tmp /= 128;
				tmp -= 57;
			} else {
				tmp = in_rssi;
				tmp = 31 - tmp;
				tmp *= -149;
				tmp /= 128;
				tmp -= 68;
			}
			if (phy->type == B43_PHYTYPE_G && adjust_2050)
				tmp += 25;
		}
		break;
	case 0x2060:
		if (in_rssi > 127)
			tmp = in_rssi - 256;
		else
			tmp = in_rssi;
		break;
	default:
		tmp = in_rssi;
		tmp -= 11;
		tmp *= 103;
		tmp /= 64;
		if (adjust_2053)
			tmp -= 109;
		else
			tmp -= 83;
	}

	return (s8) tmp;
}