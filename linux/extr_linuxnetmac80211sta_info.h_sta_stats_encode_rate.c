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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_rx_status {int bw; int enc_flags; int encoding; int nss; int rate_idx; int band; int he_gi; int he_ru; int he_dcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BW ; 
 int /*<<< orphan*/  HE_DCM ; 
 int /*<<< orphan*/  HE_GI ; 
 int /*<<< orphan*/  HE_MCS ; 
 int /*<<< orphan*/  HE_NSS ; 
 int /*<<< orphan*/  HE_RU ; 
 int /*<<< orphan*/  HT_MCS ; 
 int /*<<< orphan*/  LEGACY_BAND ; 
 int /*<<< orphan*/  LEGACY_IDX ; 
 int RX_ENC_FLAG_SHORT_GI ; 
#define  RX_ENC_HE 131 
#define  RX_ENC_HT 130 
#define  RX_ENC_LEGACY 129 
#define  RX_ENC_VHT 128 
 int /*<<< orphan*/  SGI ; 
 int /*<<< orphan*/  STA_STATS_FIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STA_STATS_RATE_INVALID ; 
 int STA_STATS_RATE_TYPE_HE ; 
 int STA_STATS_RATE_TYPE_HT ; 
 int STA_STATS_RATE_TYPE_LEGACY ; 
 int STA_STATS_RATE_TYPE_VHT ; 
 int /*<<< orphan*/  TYPE ; 
 int /*<<< orphan*/  VHT_MCS ; 
 int /*<<< orphan*/  VHT_NSS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static inline u32 sta_stats_encode_rate(struct ieee80211_rx_status *s)
{
	u32 r;

	r = STA_STATS_FIELD(BW, s->bw);

	if (s->enc_flags & RX_ENC_FLAG_SHORT_GI)
		r |= STA_STATS_FIELD(SGI, 1);

	switch (s->encoding) {
	case RX_ENC_VHT:
		r |= STA_STATS_FIELD(TYPE, STA_STATS_RATE_TYPE_VHT);
		r |= STA_STATS_FIELD(VHT_NSS, s->nss);
		r |= STA_STATS_FIELD(VHT_MCS, s->rate_idx);
		break;
	case RX_ENC_HT:
		r |= STA_STATS_FIELD(TYPE, STA_STATS_RATE_TYPE_HT);
		r |= STA_STATS_FIELD(HT_MCS, s->rate_idx);
		break;
	case RX_ENC_LEGACY:
		r |= STA_STATS_FIELD(TYPE, STA_STATS_RATE_TYPE_LEGACY);
		r |= STA_STATS_FIELD(LEGACY_BAND, s->band);
		r |= STA_STATS_FIELD(LEGACY_IDX, s->rate_idx);
		break;
	case RX_ENC_HE:
		r |= STA_STATS_FIELD(TYPE, STA_STATS_RATE_TYPE_HE);
		r |= STA_STATS_FIELD(HE_NSS, s->nss);
		r |= STA_STATS_FIELD(HE_MCS, s->rate_idx);
		r |= STA_STATS_FIELD(HE_GI, s->he_gi);
		r |= STA_STATS_FIELD(HE_RU, s->he_ru);
		r |= STA_STATS_FIELD(HE_DCM, s->he_dcm);
		break;
	default:
		WARN_ON(1);
		return STA_STATS_RATE_INVALID;
	}

	return r;
}