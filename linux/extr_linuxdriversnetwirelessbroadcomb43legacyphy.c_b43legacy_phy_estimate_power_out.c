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
struct b43legacy_phy {size_t idle_tssi; int type; scalar_t__* tssi2dbm; scalar_t__ savedpctlreg; } ;
struct b43legacy_wldev {struct b43legacy_phy phy; } ;
typedef  scalar_t__ s8 ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_BUG_ON (int) ; 
#define  B43legacy_PHYTYPE_B 129 
#define  B43legacy_PHYTYPE_G 128 
 size_t clamp_val (size_t,int,int) ; 

__attribute__((used)) static s8 b43legacy_phy_estimate_power_out(struct b43legacy_wldev *dev, s8 tssi)
{
	struct b43legacy_phy *phy = &dev->phy;
	s8 dbm = 0;
	s32 tmp;

	tmp = phy->idle_tssi;
	tmp += tssi;
	tmp -= phy->savedpctlreg;

	switch (phy->type) {
	case B43legacy_PHYTYPE_B:
	case B43legacy_PHYTYPE_G:
		tmp = clamp_val(tmp, 0x00, 0x3F);
		dbm = phy->tssi2dbm[tmp];
		break;
	default:
		B43legacy_BUG_ON(1);
	}

	return dbm;
}