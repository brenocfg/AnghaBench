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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct b43_phy {scalar_t__ type; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_tx_legacy_rate_phy_ctl_entry {int /*<<< orphan*/  modulation; int /*<<< orphan*/  coding_rate; } ;

/* Variables and functions */
 scalar_t__ B43_PHYTYPE_LP ; 
 int /*<<< orphan*/  B43_TXH_PHY1_BW_20 ; 
 int /*<<< orphan*/  B43_TXH_PHY1_MODE_SISO ; 
 scalar_t__ b43_is_cck_rate (int /*<<< orphan*/ ) ; 
 struct b43_tx_legacy_rate_phy_ctl_entry* b43_tx_legacy_rate_phy_ctl_ent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 b43_generate_tx_phy_ctl1(struct b43_wldev *dev, u8 bitrate)
{
	const struct b43_phy *phy = &dev->phy;
	const struct b43_tx_legacy_rate_phy_ctl_entry *e;
	u16 control = 0;
	u16 bw;

	if (phy->type == B43_PHYTYPE_LP)
		bw = B43_TXH_PHY1_BW_20;
	else /* FIXME */
		bw = B43_TXH_PHY1_BW_20;

	if (0) { /* FIXME: MIMO */
	} else if (b43_is_cck_rate(bitrate) && phy->type != B43_PHYTYPE_LP) {
		control = bw;
	} else {
		control = bw;
		e = b43_tx_legacy_rate_phy_ctl_ent(bitrate);
		if (e) {
			control |= e->coding_rate;
			control |= e->modulation;
		}
		control |= B43_TXH_PHY1_MODE_SISO;
	}

	return control;
}