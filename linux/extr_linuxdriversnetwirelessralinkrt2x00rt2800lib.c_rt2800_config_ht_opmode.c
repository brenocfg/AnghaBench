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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rt2x00lib_erp {int ht_opmode; int /*<<< orphan*/  cts_protection; } ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GF20_PROT_CFG ; 
 int /*<<< orphan*/  GF20_PROT_CFG_PROTECT_CTRL ; 
 int /*<<< orphan*/  GF20_PROT_CFG_PROTECT_RATE ; 
 int /*<<< orphan*/  GF40_PROT_CFG ; 
 int /*<<< orphan*/  GF40_PROT_CFG_PROTECT_CTRL ; 
 int /*<<< orphan*/  GF40_PROT_CFG_PROTECT_RATE ; 
 int IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT ; 
 int IEEE80211_HT_OP_MODE_PROTECTION ; 
#define  IEEE80211_HT_OP_MODE_PROTECTION_20MHZ 131 
#define  IEEE80211_HT_OP_MODE_PROTECTION_NONE 130 
#define  IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED 129 
#define  IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER 128 
 int /*<<< orphan*/  MM20_PROT_CFG ; 
 int /*<<< orphan*/  MM20_PROT_CFG_PROTECT_CTRL ; 
 int /*<<< orphan*/  MM20_PROT_CFG_PROTECT_RATE ; 
 int /*<<< orphan*/  MM40_PROT_CFG ; 
 int /*<<< orphan*/  MM40_PROT_CFG_PROTECT_CTRL ; 
 int /*<<< orphan*/  MM40_PROT_CFG_PROTECT_RATE ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_config_ht_opmode(struct rt2x00_dev *rt2x00dev,
				    struct rt2x00lib_erp *erp)
{
	bool any_sta_nongf = !!(erp->ht_opmode &
				IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
	u8 protection = erp->ht_opmode & IEEE80211_HT_OP_MODE_PROTECTION;
	u8 mm20_mode, mm40_mode, gf20_mode, gf40_mode;
	u16 mm20_rate, mm40_rate, gf20_rate, gf40_rate;
	u32 reg;

	/* default protection rate for HT20: OFDM 24M */
	mm20_rate = gf20_rate = 0x4004;

	/* default protection rate for HT40: duplicate OFDM 24M */
	mm40_rate = gf40_rate = 0x4084;

	switch (protection) {
	case IEEE80211_HT_OP_MODE_PROTECTION_NONE:
		/*
		 * All STAs in this BSS are HT20/40 but there might be
		 * STAs not supporting greenfield mode.
		 * => Disable protection for HT transmissions.
		 */
		mm20_mode = mm40_mode = gf20_mode = gf40_mode = 0;

		break;
	case IEEE80211_HT_OP_MODE_PROTECTION_20MHZ:
		/*
		 * All STAs in this BSS are HT20 or HT20/40 but there
		 * might be STAs not supporting greenfield mode.
		 * => Protect all HT40 transmissions.
		 */
		mm20_mode = gf20_mode = 0;
		mm40_mode = gf40_mode = 1;

		break;
	case IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER:
		/*
		 * Nonmember protection:
		 * According to 802.11n we _should_ protect all
		 * HT transmissions (but we don't have to).
		 *
		 * But if cts_protection is enabled we _shall_ protect
		 * all HT transmissions using a CCK rate.
		 *
		 * And if any station is non GF we _shall_ protect
		 * GF transmissions.
		 *
		 * We decide to protect everything
		 * -> fall through to mixed mode.
		 */
	case IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED:
		/*
		 * Legacy STAs are present
		 * => Protect all HT transmissions.
		 */
		mm20_mode = mm40_mode = gf20_mode = gf40_mode = 1;

		/*
		 * If erp protection is needed we have to protect HT
		 * transmissions with CCK 11M long preamble.
		 */
		if (erp->cts_protection) {
			/* don't duplicate RTS/CTS in CCK mode */
			mm20_rate = mm40_rate = 0x0003;
			gf20_rate = gf40_rate = 0x0003;
		}
		break;
	}

	/* check for STAs not supporting greenfield mode */
	if (any_sta_nongf)
		gf20_mode = gf40_mode = 1;

	/* Update HT protection config */
	reg = rt2800_register_read(rt2x00dev, MM20_PROT_CFG);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_PROTECT_RATE, mm20_rate);
	rt2x00_set_field32(&reg, MM20_PROT_CFG_PROTECT_CTRL, mm20_mode);
	rt2800_register_write(rt2x00dev, MM20_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, MM40_PROT_CFG);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_PROTECT_RATE, mm40_rate);
	rt2x00_set_field32(&reg, MM40_PROT_CFG_PROTECT_CTRL, mm40_mode);
	rt2800_register_write(rt2x00dev, MM40_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, GF20_PROT_CFG);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_PROTECT_RATE, gf20_rate);
	rt2x00_set_field32(&reg, GF20_PROT_CFG_PROTECT_CTRL, gf20_mode);
	rt2800_register_write(rt2x00dev, GF20_PROT_CFG, reg);

	reg = rt2800_register_read(rt2x00dev, GF40_PROT_CFG);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_PROTECT_RATE, gf40_rate);
	rt2x00_set_field32(&reg, GF40_PROT_CFG_PROTECT_CTRL, gf40_mode);
	rt2800_register_write(rt2x00dev, GF40_PROT_CFG, reg);
}