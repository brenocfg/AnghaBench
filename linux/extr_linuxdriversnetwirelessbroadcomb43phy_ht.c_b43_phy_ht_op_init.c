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
typedef  int u16 ;
struct TYPE_3__ {struct b43_phy_ht* ht; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_2__* dev; TYPE_1__ phy; } ;
struct b43_phy_ht {int tx_pwr_ctl; } ;
struct TYPE_4__ {scalar_t__ bus_type; } ;

/* Variables and functions */
 scalar_t__ B43_BUS_BCMA ; 
 int /*<<< orphan*/  B43_HTTAB16 (int,int) ; 
 int /*<<< orphan*/  B43_HTTAB32 (int,int) ; 
 int /*<<< orphan*/  B43_HTTAB_1A_C0_LATE_SIZE ; 
 int B43_PHY_EXTG (int) ; 
 int B43_PHY_HT_AFE_C1_OVER ; 
 int B43_PHY_HT_AFE_C2_OVER ; 
 int B43_PHY_HT_AFE_C3_OVER ; 
 int B43_PHY_HT_BBCFG ; 
 int B43_PHY_HT_BBCFG_RSTCCA ; 
 int /*<<< orphan*/  B43_PHY_HT_CLASS_CTL_CCK_EN ; 
 int /*<<< orphan*/  B43_PHY_HT_RF_SEQ_TRIG_RST2RX ; 
 int /*<<< orphan*/  B43_PHY_HT_RF_SEQ_TRIG_RX2TX ; 
 int B43_PHY_OFDM (int) ; 
 int EOPNOTSUPP ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_httab_0x1a_0xc0_late ; 
 int b43_httab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_httab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_httab_write_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_httab_write_few (struct b43_wldev*,int /*<<< orphan*/ ,int,int,int,...) ; 
 int /*<<< orphan*/  b43_mac_phy_clock_set (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_force_clock (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_ht_afe_unk1 (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_ht_bphy_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_ht_classifier (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_ht_force_rf_sequence (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_ht_pa_override (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_ht_read_clip_detection (struct b43_wldev*,int*) ; 
 int /*<<< orphan*/  b43_phy_ht_tables_init (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_ht_tssi_setup (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_ht_tx_power_ctl (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_ht_tx_power_ctl_idle_tssi (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_ht_tx_power_ctl_setup (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_ht_tx_power_fix (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_ht_zero_extg (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int b43_phy_ht_op_init(struct b43_wldev *dev)
{
	struct b43_phy_ht *phy_ht = dev->phy.ht;
	u16 tmp;
	u16 clip_state[3];
	bool saved_tx_pwr_ctl;

	if (dev->dev->bus_type != B43_BUS_BCMA) {
		b43err(dev->wl, "HT-PHY is supported only on BCMA bus!\n");
		return -EOPNOTSUPP;
	}

	b43_phy_ht_tables_init(dev);

	b43_phy_mask(dev, 0x0be, ~0x2);
	b43_phy_set(dev, 0x23f, 0x7ff);
	b43_phy_set(dev, 0x240, 0x7ff);
	b43_phy_set(dev, 0x241, 0x7ff);

	b43_phy_ht_zero_extg(dev);

	b43_phy_mask(dev, B43_PHY_EXTG(0), ~0x3);

	b43_phy_write(dev, B43_PHY_HT_AFE_C1_OVER, 0);
	b43_phy_write(dev, B43_PHY_HT_AFE_C2_OVER, 0);
	b43_phy_write(dev, B43_PHY_HT_AFE_C3_OVER, 0);

	b43_phy_write(dev, B43_PHY_EXTG(0x103), 0x20);
	b43_phy_write(dev, B43_PHY_EXTG(0x101), 0x20);
	b43_phy_write(dev, 0x20d, 0xb8);
	b43_phy_write(dev, B43_PHY_EXTG(0x14f), 0xc8);
	b43_phy_write(dev, 0x70, 0x50);
	b43_phy_write(dev, 0x1ff, 0x30);

	if (0) /* TODO: condition */
		; /* TODO: PHY op on reg 0x217 */

	if (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
		b43_phy_ht_classifier(dev, B43_PHY_HT_CLASS_CTL_CCK_EN, 0);
	else
		b43_phy_ht_classifier(dev, B43_PHY_HT_CLASS_CTL_CCK_EN,
				      B43_PHY_HT_CLASS_CTL_CCK_EN);

	b43_phy_set(dev, 0xb1, 0x91);
	b43_phy_write(dev, 0x32f, 0x0003);
	b43_phy_write(dev, 0x077, 0x0010);
	b43_phy_write(dev, 0x0b4, 0x0258);
	b43_phy_mask(dev, 0x17e, ~0x4000);

	b43_phy_write(dev, 0x0b9, 0x0072);

	b43_httab_write_few(dev, B43_HTTAB16(7, 0x14e), 2, 0x010f, 0x010f);
	b43_httab_write_few(dev, B43_HTTAB16(7, 0x15e), 2, 0x010f, 0x010f);
	b43_httab_write_few(dev, B43_HTTAB16(7, 0x16e), 2, 0x010f, 0x010f);

	b43_phy_ht_afe_unk1(dev);

	b43_httab_write_few(dev, B43_HTTAB16(7, 0x130), 9, 0x777, 0x111, 0x111,
			    0x777, 0x111, 0x111, 0x777, 0x111, 0x111);

	b43_httab_write(dev, B43_HTTAB16(7, 0x120), 0x0777);
	b43_httab_write(dev, B43_HTTAB16(7, 0x124), 0x0777);

	b43_httab_write(dev, B43_HTTAB16(8, 0x00), 0x02);
	b43_httab_write(dev, B43_HTTAB16(8, 0x10), 0x02);
	b43_httab_write(dev, B43_HTTAB16(8, 0x20), 0x02);

	b43_httab_write_few(dev, B43_HTTAB16(8, 0x08), 4,
			    0x8e, 0x96, 0x96, 0x96);
	b43_httab_write_few(dev, B43_HTTAB16(8, 0x18), 4,
			    0x8f, 0x9f, 0x9f, 0x9f);
	b43_httab_write_few(dev, B43_HTTAB16(8, 0x28), 4,
			    0x8f, 0x9f, 0x9f, 0x9f);

	b43_httab_write_few(dev, B43_HTTAB16(8, 0x0c), 4, 0x2, 0x2, 0x2, 0x2);
	b43_httab_write_few(dev, B43_HTTAB16(8, 0x1c), 4, 0x2, 0x2, 0x2, 0x2);
	b43_httab_write_few(dev, B43_HTTAB16(8, 0x2c), 4, 0x2, 0x2, 0x2, 0x2);

	b43_phy_maskset(dev, 0x0280, 0xff00, 0x3e);
	b43_phy_maskset(dev, 0x0283, 0xff00, 0x3e);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x0141), 0xff00, 0x46);
	b43_phy_maskset(dev, 0x0283, 0xff00, 0x40);

	b43_httab_write_few(dev, B43_HTTAB16(00, 0x8), 4,
			    0x09, 0x0e, 0x13, 0x18);
	b43_httab_write_few(dev, B43_HTTAB16(01, 0x8), 4,
			    0x09, 0x0e, 0x13, 0x18);
	/* TODO: Did wl mean 2 instead of 40? */
	b43_httab_write_few(dev, B43_HTTAB16(40, 0x8), 4,
			    0x09, 0x0e, 0x13, 0x18);

	b43_phy_maskset(dev, B43_PHY_OFDM(0x24), 0x3f, 0xd);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x64), 0x3f, 0xd);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xa4), 0x3f, 0xd);

	b43_phy_set(dev, B43_PHY_EXTG(0x060), 0x1);
	b43_phy_set(dev, B43_PHY_EXTG(0x064), 0x1);
	b43_phy_set(dev, B43_PHY_EXTG(0x080), 0x1);
	b43_phy_set(dev, B43_PHY_EXTG(0x084), 0x1);

	/* Copy some tables entries */
	tmp = b43_httab_read(dev, B43_HTTAB16(7, 0x144));
	b43_httab_write(dev, B43_HTTAB16(7, 0x14a), tmp);
	tmp = b43_httab_read(dev, B43_HTTAB16(7, 0x154));
	b43_httab_write(dev, B43_HTTAB16(7, 0x15a), tmp);
	tmp = b43_httab_read(dev, B43_HTTAB16(7, 0x164));
	b43_httab_write(dev, B43_HTTAB16(7, 0x16a), tmp);

	/* Reset CCA */
	b43_phy_force_clock(dev, true);
	tmp = b43_phy_read(dev, B43_PHY_HT_BBCFG);
	b43_phy_write(dev, B43_PHY_HT_BBCFG, tmp | B43_PHY_HT_BBCFG_RSTCCA);
	b43_phy_write(dev, B43_PHY_HT_BBCFG, tmp & ~B43_PHY_HT_BBCFG_RSTCCA);
	b43_phy_force_clock(dev, false);

	b43_mac_phy_clock_set(dev, true);

	b43_phy_ht_pa_override(dev, false);
	b43_phy_ht_force_rf_sequence(dev, B43_PHY_HT_RF_SEQ_TRIG_RX2TX);
	b43_phy_ht_force_rf_sequence(dev, B43_PHY_HT_RF_SEQ_TRIG_RST2RX);
	b43_phy_ht_pa_override(dev, true);

	/* TODO: Should we restore it? Or store it in global PHY info? */
	b43_phy_ht_classifier(dev, 0, 0);
	b43_phy_ht_read_clip_detection(dev, clip_state);

	if (b43_current_band(dev->wl) == NL80211_BAND_2GHZ)
		b43_phy_ht_bphy_init(dev);

	b43_httab_write_bulk(dev, B43_HTTAB32(0x1a, 0xc0),
			B43_HTTAB_1A_C0_LATE_SIZE, b43_httab_0x1a_0xc0_late);

	saved_tx_pwr_ctl = phy_ht->tx_pwr_ctl;
	b43_phy_ht_tx_power_fix(dev);
	b43_phy_ht_tx_power_ctl(dev, false);
	b43_phy_ht_tx_power_ctl_idle_tssi(dev);
	b43_phy_ht_tx_power_ctl_setup(dev);
	b43_phy_ht_tssi_setup(dev);
	b43_phy_ht_tx_power_ctl(dev, saved_tx_pwr_ctl);

	return 0;
}