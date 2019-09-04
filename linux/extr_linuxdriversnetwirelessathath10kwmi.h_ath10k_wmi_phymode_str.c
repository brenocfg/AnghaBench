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
typedef  enum wmi_phy_mode { ____Placeholder_wmi_phy_mode } wmi_phy_mode ;

/* Variables and functions */
#define  MODE_11A 144 
#define  MODE_11AC_VHT160 143 
#define  MODE_11AC_VHT20 142 
#define  MODE_11AC_VHT20_2G 141 
#define  MODE_11AC_VHT40 140 
#define  MODE_11AC_VHT40_2G 139 
#define  MODE_11AC_VHT80 138 
#define  MODE_11AC_VHT80_2G 137 
#define  MODE_11AC_VHT80_80 136 
#define  MODE_11B 135 
#define  MODE_11G 134 
#define  MODE_11GONLY 133 
#define  MODE_11NA_HT20 132 
#define  MODE_11NA_HT40 131 
#define  MODE_11NG_HT20 130 
#define  MODE_11NG_HT40 129 
#define  MODE_UNKNOWN 128 

__attribute__((used)) static inline const char *ath10k_wmi_phymode_str(enum wmi_phy_mode mode)
{
	switch (mode) {
	case MODE_11A:
		return "11a";
	case MODE_11G:
		return "11g";
	case MODE_11B:
		return "11b";
	case MODE_11GONLY:
		return "11gonly";
	case MODE_11NA_HT20:
		return "11na-ht20";
	case MODE_11NG_HT20:
		return "11ng-ht20";
	case MODE_11NA_HT40:
		return "11na-ht40";
	case MODE_11NG_HT40:
		return "11ng-ht40";
	case MODE_11AC_VHT20:
		return "11ac-vht20";
	case MODE_11AC_VHT40:
		return "11ac-vht40";
	case MODE_11AC_VHT80:
		return "11ac-vht80";
	case MODE_11AC_VHT160:
		return "11ac-vht160";
	case MODE_11AC_VHT80_80:
		return "11ac-vht80+80";
	case MODE_11AC_VHT20_2G:
		return "11ac-vht20-2g";
	case MODE_11AC_VHT40_2G:
		return "11ac-vht40-2g";
	case MODE_11AC_VHT80_2G:
		return "11ac-vht80-2g";
	case MODE_UNKNOWN:
		/* skip */
		break;

		/* no default handler to allow compiler to check that the
		 * enum is fully handled
		 */
	};

	return "<unknown>";
}