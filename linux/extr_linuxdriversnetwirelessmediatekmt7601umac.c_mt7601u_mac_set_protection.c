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
typedef  int u32 ;
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT ; 
 int IEEE80211_HT_OP_MODE_PROTECTION ; 
#define  IEEE80211_HT_OP_MODE_PROTECTION_20MHZ 131 
#define  IEEE80211_HT_OP_MODE_PROTECTION_NONE 130 
#define  IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED 129 
#define  IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER 128 
 scalar_t__ MT_CCK_PROT_CFG ; 
 int MT_PROT_CTRL_CTS2SELF ; 
 int MT_PROT_CTRL_RTS_CTS ; 
 int MT_PROT_NAV_SHORT ; 
 int MT_PROT_RATE_CCK_11 ; 
 int MT_PROT_RATE_DUP_OFDM_24 ; 
 int MT_PROT_RATE_OFDM_24 ; 
 int MT_PROT_RTS_THR_EN ; 
 int MT_PROT_TXOP_ALLOW_ALL ; 
 int MT_PROT_TXOP_ALLOW_BW20 ; 
 int /*<<< orphan*/  mt7601u_wr (struct mt7601u_dev*,scalar_t__,int) ; 

void mt7601u_mac_set_protection(struct mt7601u_dev *dev, bool legacy_prot,
				int ht_mode)
{
	int mode = ht_mode & IEEE80211_HT_OP_MODE_PROTECTION;
	bool non_gf = !!(ht_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
	u32 prot[6];
	bool ht_rts[4] = {};
	int i;

	prot[0] = MT_PROT_NAV_SHORT |
		  MT_PROT_TXOP_ALLOW_ALL |
		  MT_PROT_RTS_THR_EN;
	prot[1] = prot[0];
	if (legacy_prot)
		prot[1] |= MT_PROT_CTRL_CTS2SELF;

	prot[2] = prot[4] = MT_PROT_NAV_SHORT | MT_PROT_TXOP_ALLOW_BW20;
	prot[3] = prot[5] = MT_PROT_NAV_SHORT | MT_PROT_TXOP_ALLOW_ALL;

	if (legacy_prot) {
		prot[2] |= MT_PROT_RATE_CCK_11;
		prot[3] |= MT_PROT_RATE_CCK_11;
		prot[4] |= MT_PROT_RATE_CCK_11;
		prot[5] |= MT_PROT_RATE_CCK_11;
	} else {
		prot[2] |= MT_PROT_RATE_OFDM_24;
		prot[3] |= MT_PROT_RATE_DUP_OFDM_24;
		prot[4] |= MT_PROT_RATE_OFDM_24;
		prot[5] |= MT_PROT_RATE_DUP_OFDM_24;
	}

	switch (mode) {
	case IEEE80211_HT_OP_MODE_PROTECTION_NONE:
		break;

	case IEEE80211_HT_OP_MODE_PROTECTION_NONMEMBER:
		ht_rts[0] = ht_rts[1] = ht_rts[2] = ht_rts[3] = true;
		break;

	case IEEE80211_HT_OP_MODE_PROTECTION_20MHZ:
		ht_rts[1] = ht_rts[3] = true;
		break;

	case IEEE80211_HT_OP_MODE_PROTECTION_NONHT_MIXED:
		ht_rts[0] = ht_rts[1] = ht_rts[2] = ht_rts[3] = true;
		break;
	}

	if (non_gf)
		ht_rts[2] = ht_rts[3] = true;

	for (i = 0; i < 4; i++)
		if (ht_rts[i])
			prot[i + 2] |= MT_PROT_CTRL_RTS_CTS;

	for (i = 0; i < 6; i++)
		mt7601u_wr(dev, MT_CCK_PROT_CFG + i * 4, prot[i]);
}