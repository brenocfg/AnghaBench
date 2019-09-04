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
struct mt76_rx_status {int rate_idx; int enc_flags; int nss; int /*<<< orphan*/  bw; int /*<<< orphan*/  encoding; int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int EINVAL ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
#define  MT_PHY_BW_20 135 
#define  MT_PHY_BW_40 134 
#define  MT_PHY_BW_80 133 
#define  MT_PHY_TYPE_CCK 132 
#define  MT_PHY_TYPE_HT 131 
#define  MT_PHY_TYPE_HT_GF 130 
#define  MT_PHY_TYPE_OFDM 129 
#define  MT_PHY_TYPE_VHT 128 
 int /*<<< orphan*/  MT_RATE_INDEX_VHT_IDX ; 
 int /*<<< orphan*/  MT_RATE_INDEX_VHT_NSS ; 
 int /*<<< orphan*/  MT_RXWI_RATE_BW ; 
 int /*<<< orphan*/  MT_RXWI_RATE_INDEX ; 
 int MT_RXWI_RATE_LDPC ; 
 int /*<<< orphan*/  MT_RXWI_RATE_PHY ; 
 int MT_RXWI_RATE_SGI ; 
 int MT_RXWI_RATE_STBC ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  RATE_INFO_BW_40 ; 
 int /*<<< orphan*/  RATE_INFO_BW_80 ; 
 int RX_ENC_FLAG_HT_GF ; 
 int RX_ENC_FLAG_LDPC ; 
 int RX_ENC_FLAG_SHORTPRE ; 
 int RX_ENC_FLAG_SHORT_GI ; 
 int RX_ENC_FLAG_STBC_SHIFT ; 
 int /*<<< orphan*/  RX_ENC_HT ; 
 int /*<<< orphan*/  RX_ENC_VHT ; 

__attribute__((used)) static int
mt76x2_mac_process_rate(struct mt76_rx_status *status, u16 rate)
{
	u8 idx = FIELD_GET(MT_RXWI_RATE_INDEX, rate);

	switch (FIELD_GET(MT_RXWI_RATE_PHY, rate)) {
	case MT_PHY_TYPE_OFDM:
		if (idx >= 8)
			idx = 0;

		if (status->band == NL80211_BAND_2GHZ)
			idx += 4;

		status->rate_idx = idx;
		return 0;
	case MT_PHY_TYPE_CCK:
		if (idx >= 8) {
			idx -= 8;
			status->enc_flags |= RX_ENC_FLAG_SHORTPRE;
		}

		if (idx >= 4)
			idx = 0;

		status->rate_idx = idx;
		return 0;
	case MT_PHY_TYPE_HT_GF:
		status->enc_flags |= RX_ENC_FLAG_HT_GF;
		/* fall through */
	case MT_PHY_TYPE_HT:
		status->encoding = RX_ENC_HT;
		status->rate_idx = idx;
		break;
	case MT_PHY_TYPE_VHT:
		status->encoding = RX_ENC_VHT;
		status->rate_idx = FIELD_GET(MT_RATE_INDEX_VHT_IDX, idx);
		status->nss = FIELD_GET(MT_RATE_INDEX_VHT_NSS, idx) + 1;
		break;
	default:
		return -EINVAL;
	}

	if (rate & MT_RXWI_RATE_LDPC)
		status->enc_flags |= RX_ENC_FLAG_LDPC;

	if (rate & MT_RXWI_RATE_SGI)
		status->enc_flags |= RX_ENC_FLAG_SHORT_GI;

	if (rate & MT_RXWI_RATE_STBC)
		status->enc_flags |= 1 << RX_ENC_FLAG_STBC_SHIFT;

	switch (FIELD_GET(MT_RXWI_RATE_BW, rate)) {
	case MT_PHY_BW_20:
		break;
	case MT_PHY_BW_40:
		status->bw = RATE_INFO_BW_40;
		break;
	case MT_PHY_BW_80:
		status->bw = RATE_INFO_BW_80;
		break;
	default:
		break;
	}

	return 0;
}