#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct ssb_sprom {TYPE_5__* core_pwr_info; } ;
struct TYPE_9__ {TYPE_3__* chandef; struct b43_phy_ht* ht; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_4__ phy; TYPE_1__* dev; } ;
struct b43_phy_ht {int* idle_tssi; } ;
typedef  int s32 ;
typedef  int s16 ;
struct TYPE_10__ {int maxpwr_2g; int* pa_2g; int maxpwr_5gl; int* pa_5gl; int maxpwr_5g; int* pa_5g; int maxpwr_5gh; int* pa_5gh; } ;
struct TYPE_8__ {TYPE_2__* chan; } ;
struct TYPE_7__ {int center_freq; } ;
struct TYPE_6__ {struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_HTTAB16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B43_PHY_HT_TSSIMODE ; 
 int B43_PHY_HT_TSSIMODE_EN ; 
 int /*<<< orphan*/  B43_PHY_HT_TXPCTL_CMD_C1 ; 
 int B43_PHY_HT_TXPCTL_CMD_C1_INIT ; 
 int B43_PHY_HT_TXPCTL_CMD_C1_PCTLEN ; 
 int /*<<< orphan*/  B43_PHY_HT_TXPCTL_CMD_C2 ; 
 int B43_PHY_HT_TXPCTL_CMD_C2_INIT ; 
 int /*<<< orphan*/  B43_PHY_HT_TXPCTL_CMD_C3 ; 
 int B43_PHY_HT_TXPCTL_CMD_C3_INIT ; 
 int /*<<< orphan*/  B43_PHY_HT_TXPCTL_IDLE_TSSI ; 
 int /*<<< orphan*/  B43_PHY_HT_TXPCTL_IDLE_TSSI2 ; 
 int B43_PHY_HT_TXPCTL_IDLE_TSSI2_C3 ; 
 int B43_PHY_HT_TXPCTL_IDLE_TSSI2_C3_SHIFT ; 
 int B43_PHY_HT_TXPCTL_IDLE_TSSI_BINF ; 
 int B43_PHY_HT_TXPCTL_IDLE_TSSI_C1 ; 
 int B43_PHY_HT_TXPCTL_IDLE_TSSI_C1_SHIFT ; 
 int B43_PHY_HT_TXPCTL_IDLE_TSSI_C2 ; 
 int B43_PHY_HT_TXPCTL_IDLE_TSSI_C2_SHIFT ; 
 int /*<<< orphan*/  B43_PHY_HT_TXPCTL_N ; 
 int B43_PHY_HT_TXPCTL_N_NPTIL2 ; 
 int B43_PHY_HT_TXPCTL_N_NPTIL2_SHIFT ; 
 int B43_PHY_HT_TXPCTL_N_TSSID ; 
 int /*<<< orphan*/  B43_PHY_HT_TXPCTL_TARG_PWR ; 
 int /*<<< orphan*/  B43_PHY_HT_TXPCTL_TARG_PWR2 ; 
 int B43_PHY_HT_TXPCTL_TARG_PWR2_C3 ; 
 int B43_PHY_HT_TXPCTL_TARG_PWR2_C3_SHIFT ; 
 int B43_PHY_HT_TXPCTL_TARG_PWR_C1 ; 
 int B43_PHY_HT_TXPCTL_TARG_PWR_C1_SHIFT ; 
 int B43_PHY_HT_TXPCTL_TARG_PWR_C2 ; 
 int B43_PHY_HT_TXPCTL_TARG_PWR_C2_SHIFT ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_httab_write_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int max (int,int) ; 

__attribute__((used)) static void b43_phy_ht_tx_power_ctl_setup(struct b43_wldev *dev)
{
	struct b43_phy_ht *phy_ht = dev->phy.ht;
	struct ssb_sprom *sprom = dev->dev->bus_sprom;

	u8 *idle = phy_ht->idle_tssi;
	u8 target[3];
	s16 a1[3], b0[3], b1[3];

	u16 freq = dev->phy.chandef->chan->center_freq;
	int i, c;

	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ) {
		for (c = 0; c < 3; c++) {
			target[c] = sprom->core_pwr_info[c].maxpwr_2g;
			a1[c] = sprom->core_pwr_info[c].pa_2g[0];
			b0[c] = sprom->core_pwr_info[c].pa_2g[1];
			b1[c] = sprom->core_pwr_info[c].pa_2g[2];
		}
	} else if (freq >= 4900 && freq < 5100) {
		for (c = 0; c < 3; c++) {
			target[c] = sprom->core_pwr_info[c].maxpwr_5gl;
			a1[c] = sprom->core_pwr_info[c].pa_5gl[0];
			b0[c] = sprom->core_pwr_info[c].pa_5gl[1];
			b1[c] = sprom->core_pwr_info[c].pa_5gl[2];
		}
	} else if (freq >= 5100 && freq < 5500) {
		for (c = 0; c < 3; c++) {
			target[c] = sprom->core_pwr_info[c].maxpwr_5g;
			a1[c] = sprom->core_pwr_info[c].pa_5g[0];
			b0[c] = sprom->core_pwr_info[c].pa_5g[1];
			b1[c] = sprom->core_pwr_info[c].pa_5g[2];
		}
	} else if (freq >= 5500) {
		for (c = 0; c < 3; c++) {
			target[c] = sprom->core_pwr_info[c].maxpwr_5gh;
			a1[c] = sprom->core_pwr_info[c].pa_5gh[0];
			b0[c] = sprom->core_pwr_info[c].pa_5gh[1];
			b1[c] = sprom->core_pwr_info[c].pa_5gh[2];
		}
	} else {
		target[0] = target[1] = target[2] = 52;
		a1[0] = a1[1] = a1[2] = -424;
		b0[0] = b0[1] = b0[2] = 5612;
		b1[0] = b1[1] = b1[2] = -1393;
	}

	b43_phy_set(dev, B43_PHY_HT_TSSIMODE, B43_PHY_HT_TSSIMODE_EN);
	b43_phy_mask(dev, B43_PHY_HT_TXPCTL_CMD_C1,
		     ~B43_PHY_HT_TXPCTL_CMD_C1_PCTLEN & 0xFFFF);

	/* TODO: Does it depend on sprom->fem.ghz2.tssipos? */
	b43_phy_set(dev, B43_PHY_HT_TXPCTL_IDLE_TSSI, 0x4000);

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_CMD_C1,
			~B43_PHY_HT_TXPCTL_CMD_C1_INIT, 0x19);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_CMD_C2,
			~B43_PHY_HT_TXPCTL_CMD_C2_INIT, 0x19);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_CMD_C3,
			~B43_PHY_HT_TXPCTL_CMD_C3_INIT, 0x19);

	b43_phy_set(dev, B43_PHY_HT_TXPCTL_IDLE_TSSI,
		    B43_PHY_HT_TXPCTL_IDLE_TSSI_BINF);

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_IDLE_TSSI,
			~B43_PHY_HT_TXPCTL_IDLE_TSSI_C1,
			idle[0] << B43_PHY_HT_TXPCTL_IDLE_TSSI_C1_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_IDLE_TSSI,
			~B43_PHY_HT_TXPCTL_IDLE_TSSI_C2,
			idle[1] << B43_PHY_HT_TXPCTL_IDLE_TSSI_C2_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_IDLE_TSSI2,
			~B43_PHY_HT_TXPCTL_IDLE_TSSI2_C3,
			idle[2] << B43_PHY_HT_TXPCTL_IDLE_TSSI2_C3_SHIFT);

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_N, ~B43_PHY_HT_TXPCTL_N_TSSID,
			0xf0);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_N, ~B43_PHY_HT_TXPCTL_N_NPTIL2,
			0x3 << B43_PHY_HT_TXPCTL_N_NPTIL2_SHIFT);
#if 0
	/* TODO: what to mask/set? */
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_CMD_C1, 0x800, 0)
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_CMD_C1, 0x400, 0)
#endif

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_TARG_PWR,
			~B43_PHY_HT_TXPCTL_TARG_PWR_C1,
			target[0] << B43_PHY_HT_TXPCTL_TARG_PWR_C1_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_TARG_PWR,
			~B43_PHY_HT_TXPCTL_TARG_PWR_C2 & 0xFFFF,
			target[1] << B43_PHY_HT_TXPCTL_TARG_PWR_C2_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTL_TARG_PWR2,
			~B43_PHY_HT_TXPCTL_TARG_PWR2_C3,
			target[2] << B43_PHY_HT_TXPCTL_TARG_PWR2_C3_SHIFT);

	for (c = 0; c < 3; c++) {
		s32 num, den, pwr;
		u32 regval[64];

		for (i = 0; i < 64; i++) {
			num = 8 * (16 * b0[c] + b1[c] * i);
			den = 32768 + a1[c] * i;
			pwr = max((4 * num + den / 2) / den, -8);
			regval[i] = pwr;
		}
		b43_httab_write_bulk(dev, B43_HTTAB16(26 + c, 0), 64, regval);
	}
}