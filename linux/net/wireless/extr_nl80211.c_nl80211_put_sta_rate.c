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
typedef  unsigned long u32 ;
typedef  unsigned long u16 ;
struct sk_buff {int dummy; } ;
struct rate_info {int bw; int flags; int /*<<< orphan*/  he_ru_alloc; int /*<<< orphan*/  he_dcm; int /*<<< orphan*/  he_gi; int /*<<< orphan*/  nss; int /*<<< orphan*/  mcs; } ;
struct nlattr {int dummy; } ;
typedef  enum nl80211_rate_info { ____Placeholder_nl80211_rate_info } nl80211_rate_info ;

/* Variables and functions */
 int NL80211_RATE_INFO_10_MHZ_WIDTH ; 
 int NL80211_RATE_INFO_160_MHZ_WIDTH ; 
 int NL80211_RATE_INFO_40_MHZ_WIDTH ; 
 int NL80211_RATE_INFO_5_MHZ_WIDTH ; 
 int NL80211_RATE_INFO_80_MHZ_WIDTH ; 
 int /*<<< orphan*/  NL80211_RATE_INFO_BITRATE ; 
 int /*<<< orphan*/  NL80211_RATE_INFO_BITRATE32 ; 
 int /*<<< orphan*/  NL80211_RATE_INFO_HE_DCM ; 
 int /*<<< orphan*/  NL80211_RATE_INFO_HE_GI ; 
 int /*<<< orphan*/  NL80211_RATE_INFO_HE_MCS ; 
 int /*<<< orphan*/  NL80211_RATE_INFO_HE_NSS ; 
 int /*<<< orphan*/  NL80211_RATE_INFO_HE_RU_ALLOC ; 
 int /*<<< orphan*/  NL80211_RATE_INFO_MCS ; 
 int NL80211_RATE_INFO_SHORT_GI ; 
 int /*<<< orphan*/  NL80211_RATE_INFO_VHT_MCS ; 
 int /*<<< orphan*/  NL80211_RATE_INFO_VHT_NSS ; 
#define  RATE_INFO_BW_10 134 
#define  RATE_INFO_BW_160 133 
#define  RATE_INFO_BW_20 132 
#define  RATE_INFO_BW_40 131 
#define  RATE_INFO_BW_5 130 
#define  RATE_INFO_BW_80 129 
#define  RATE_INFO_BW_HE_RU 128 
 int RATE_INFO_FLAGS_HE_MCS ; 
 int RATE_INFO_FLAGS_MCS ; 
 int RATE_INFO_FLAGS_SHORT_GI ; 
 int RATE_INFO_FLAGS_VHT_MCS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long cfg80211_calculate_bitrate (struct rate_info*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int) ; 
 scalar_t__ nla_put_flag (struct sk_buff*,int) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool nl80211_put_sta_rate(struct sk_buff *msg, struct rate_info *info, int attr)
{
	struct nlattr *rate;
	u32 bitrate;
	u16 bitrate_compat;
	enum nl80211_rate_info rate_flg;

	rate = nla_nest_start_noflag(msg, attr);
	if (!rate)
		return false;

	/* cfg80211_calculate_bitrate will return 0 for mcs >= 32 */
	bitrate = cfg80211_calculate_bitrate(info);
	/* report 16-bit bitrate only if we can */
	bitrate_compat = bitrate < (1UL << 16) ? bitrate : 0;
	if (bitrate > 0 &&
	    nla_put_u32(msg, NL80211_RATE_INFO_BITRATE32, bitrate))
		return false;
	if (bitrate_compat > 0 &&
	    nla_put_u16(msg, NL80211_RATE_INFO_BITRATE, bitrate_compat))
		return false;

	switch (info->bw) {
	case RATE_INFO_BW_5:
		rate_flg = NL80211_RATE_INFO_5_MHZ_WIDTH;
		break;
	case RATE_INFO_BW_10:
		rate_flg = NL80211_RATE_INFO_10_MHZ_WIDTH;
		break;
	default:
		WARN_ON(1);
		/* fall through */
	case RATE_INFO_BW_20:
		rate_flg = 0;
		break;
	case RATE_INFO_BW_40:
		rate_flg = NL80211_RATE_INFO_40_MHZ_WIDTH;
		break;
	case RATE_INFO_BW_80:
		rate_flg = NL80211_RATE_INFO_80_MHZ_WIDTH;
		break;
	case RATE_INFO_BW_160:
		rate_flg = NL80211_RATE_INFO_160_MHZ_WIDTH;
		break;
	case RATE_INFO_BW_HE_RU:
		rate_flg = 0;
		WARN_ON(!(info->flags & RATE_INFO_FLAGS_HE_MCS));
	}

	if (rate_flg && nla_put_flag(msg, rate_flg))
		return false;

	if (info->flags & RATE_INFO_FLAGS_MCS) {
		if (nla_put_u8(msg, NL80211_RATE_INFO_MCS, info->mcs))
			return false;
		if (info->flags & RATE_INFO_FLAGS_SHORT_GI &&
		    nla_put_flag(msg, NL80211_RATE_INFO_SHORT_GI))
			return false;
	} else if (info->flags & RATE_INFO_FLAGS_VHT_MCS) {
		if (nla_put_u8(msg, NL80211_RATE_INFO_VHT_MCS, info->mcs))
			return false;
		if (nla_put_u8(msg, NL80211_RATE_INFO_VHT_NSS, info->nss))
			return false;
		if (info->flags & RATE_INFO_FLAGS_SHORT_GI &&
		    nla_put_flag(msg, NL80211_RATE_INFO_SHORT_GI))
			return false;
	} else if (info->flags & RATE_INFO_FLAGS_HE_MCS) {
		if (nla_put_u8(msg, NL80211_RATE_INFO_HE_MCS, info->mcs))
			return false;
		if (nla_put_u8(msg, NL80211_RATE_INFO_HE_NSS, info->nss))
			return false;
		if (nla_put_u8(msg, NL80211_RATE_INFO_HE_GI, info->he_gi))
			return false;
		if (nla_put_u8(msg, NL80211_RATE_INFO_HE_DCM, info->he_dcm))
			return false;
		if (info->bw == RATE_INFO_BW_HE_RU &&
		    nla_put_u8(msg, NL80211_RATE_INFO_HE_RU_ALLOC,
			       info->he_ru_alloc))
			return false;
	}

	nla_nest_end(msg, rate);
	return true;
}