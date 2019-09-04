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
struct rtl_regulatory {int country_code; } ;
struct ieee80211_regdomain {int dummy; } ;

/* Variables and functions */
#define  COUNTRY_CODE_ETSI 141 
#define  COUNTRY_CODE_FCC 140 
#define  COUNTRY_CODE_FRANCE 139 
#define  COUNTRY_CODE_GLOBAL_DOMAIN 138 
#define  COUNTRY_CODE_IC 137 
#define  COUNTRY_CODE_ISRAEL 136 
#define  COUNTRY_CODE_MIC 135 
#define  COUNTRY_CODE_MKK 134 
#define  COUNTRY_CODE_MKK1 133 
#define  COUNTRY_CODE_SPAIN 132 
#define  COUNTRY_CODE_TELEC 131 
#define  COUNTRY_CODE_TELEC_NETGEAR 130 
#define  COUNTRY_CODE_WORLD_WIDE_13 129 
#define  COUNTRY_CODE_WORLD_WIDE_13_5G_ALL 128 
 struct ieee80211_regdomain const rtl_regdom_11 ; 
 struct ieee80211_regdomain const rtl_regdom_12_13 ; 
 struct ieee80211_regdomain const rtl_regdom_12_13_5g_all ; 
 struct ieee80211_regdomain const rtl_regdom_14 ; 
 struct ieee80211_regdomain const rtl_regdom_14_60_64 ; 
 struct ieee80211_regdomain const rtl_regdom_60_64 ; 
 struct ieee80211_regdomain const rtl_regdom_no_midband ; 

__attribute__((used)) static const struct ieee80211_regdomain *_rtl_regdomain_select(
						struct rtl_regulatory *reg)
{
	switch (reg->country_code) {
	case COUNTRY_CODE_FCC:
		return &rtl_regdom_no_midband;
	case COUNTRY_CODE_IC:
		return &rtl_regdom_11;
	case COUNTRY_CODE_TELEC_NETGEAR:
		return &rtl_regdom_60_64;
	case COUNTRY_CODE_ETSI:
	case COUNTRY_CODE_SPAIN:
	case COUNTRY_CODE_FRANCE:
	case COUNTRY_CODE_ISRAEL:
		return &rtl_regdom_12_13;
	case COUNTRY_CODE_MKK:
	case COUNTRY_CODE_MKK1:
	case COUNTRY_CODE_TELEC:
	case COUNTRY_CODE_MIC:
		return &rtl_regdom_14_60_64;
	case COUNTRY_CODE_GLOBAL_DOMAIN:
		return &rtl_regdom_14;
	case COUNTRY_CODE_WORLD_WIDE_13:
	case COUNTRY_CODE_WORLD_WIDE_13_5G_ALL:
		return &rtl_regdom_12_13_5g_all;
	default:
		return &rtl_regdom_no_midband;
	}
}