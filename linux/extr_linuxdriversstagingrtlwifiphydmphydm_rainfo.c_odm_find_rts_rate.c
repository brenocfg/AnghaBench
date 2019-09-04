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
struct phy_dm_struct {int* band_type; } ;

/* Variables and functions */
#define  ODM_RATE11M 185 
#define  ODM_RATE12M 184 
#define  ODM_RATE18M 183 
#define  ODM_RATE1M 182 
#define  ODM_RATE24M 181 
#define  ODM_RATE2M 180 
#define  ODM_RATE36M 179 
#define  ODM_RATE48M 178 
#define  ODM_RATE54M 177 
#define  ODM_RATE5_5M 176 
#define  ODM_RATE6M 175 
#define  ODM_RATE9M 174 
#define  ODM_RATEMCS0 173 
#define  ODM_RATEMCS1 172 
#define  ODM_RATEMCS10 171 
#define  ODM_RATEMCS11 170 
#define  ODM_RATEMCS12 169 
#define  ODM_RATEMCS13 168 
#define  ODM_RATEMCS14 167 
#define  ODM_RATEMCS15 166 
#define  ODM_RATEMCS2 165 
#define  ODM_RATEMCS3 164 
#define  ODM_RATEMCS4 163 
#define  ODM_RATEMCS5 162 
#define  ODM_RATEMCS6 161 
#define  ODM_RATEMCS7 160 
#define  ODM_RATEMCS8 159 
#define  ODM_RATEMCS9 158 
#define  ODM_RATEVHTSS1MCS0 157 
#define  ODM_RATEVHTSS1MCS1 156 
#define  ODM_RATEVHTSS1MCS2 155 
#define  ODM_RATEVHTSS1MCS3 154 
#define  ODM_RATEVHTSS1MCS4 153 
#define  ODM_RATEVHTSS1MCS5 152 
#define  ODM_RATEVHTSS1MCS6 151 
#define  ODM_RATEVHTSS1MCS7 150 
#define  ODM_RATEVHTSS1MCS8 149 
#define  ODM_RATEVHTSS1MCS9 148 
#define  ODM_RATEVHTSS2MCS0 147 
#define  ODM_RATEVHTSS2MCS1 146 
#define  ODM_RATEVHTSS2MCS2 145 
#define  ODM_RATEVHTSS2MCS3 144 
#define  ODM_RATEVHTSS2MCS4 143 
#define  ODM_RATEVHTSS2MCS5 142 
#define  ODM_RATEVHTSS2MCS6 141 
#define  ODM_RATEVHTSS2MCS7 140 
#define  ODM_RATEVHTSS2MCS8 139 
#define  ODM_RATEVHTSS2MCS9 138 
#define  ODM_RATEVHTSS3MCS0 137 
#define  ODM_RATEVHTSS3MCS1 136 
#define  ODM_RATEVHTSS3MCS2 135 
#define  ODM_RATEVHTSS3MCS3 134 
#define  ODM_RATEVHTSS3MCS4 133 
#define  ODM_RATEVHTSS3MCS5 132 
#define  ODM_RATEVHTSS3MCS6 131 
#define  ODM_RATEVHTSS3MCS7 130 
#define  ODM_RATEVHTSS3MCS8 129 
#define  ODM_RATEVHTSS3MCS9 128 

u8 odm_find_rts_rate(void *dm_void, u8 tx_rate, bool is_erp_protect)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	u8 rts_ini_rate = ODM_RATE6M;

	if (is_erp_protect) { /* use CCK rate as RTS*/
		rts_ini_rate = ODM_RATE1M;
	} else {
		switch (tx_rate) {
		case ODM_RATEVHTSS3MCS9:
		case ODM_RATEVHTSS3MCS8:
		case ODM_RATEVHTSS3MCS7:
		case ODM_RATEVHTSS3MCS6:
		case ODM_RATEVHTSS3MCS5:
		case ODM_RATEVHTSS3MCS4:
		case ODM_RATEVHTSS3MCS3:
		case ODM_RATEVHTSS2MCS9:
		case ODM_RATEVHTSS2MCS8:
		case ODM_RATEVHTSS2MCS7:
		case ODM_RATEVHTSS2MCS6:
		case ODM_RATEVHTSS2MCS5:
		case ODM_RATEVHTSS2MCS4:
		case ODM_RATEVHTSS2MCS3:
		case ODM_RATEVHTSS1MCS9:
		case ODM_RATEVHTSS1MCS8:
		case ODM_RATEVHTSS1MCS7:
		case ODM_RATEVHTSS1MCS6:
		case ODM_RATEVHTSS1MCS5:
		case ODM_RATEVHTSS1MCS4:
		case ODM_RATEVHTSS1MCS3:
		case ODM_RATEMCS15:
		case ODM_RATEMCS14:
		case ODM_RATEMCS13:
		case ODM_RATEMCS12:
		case ODM_RATEMCS11:
		case ODM_RATEMCS7:
		case ODM_RATEMCS6:
		case ODM_RATEMCS5:
		case ODM_RATEMCS4:
		case ODM_RATEMCS3:
		case ODM_RATE54M:
		case ODM_RATE48M:
		case ODM_RATE36M:
		case ODM_RATE24M:
			rts_ini_rate = ODM_RATE24M;
			break;
		case ODM_RATEVHTSS3MCS2:
		case ODM_RATEVHTSS3MCS1:
		case ODM_RATEVHTSS2MCS2:
		case ODM_RATEVHTSS2MCS1:
		case ODM_RATEVHTSS1MCS2:
		case ODM_RATEVHTSS1MCS1:
		case ODM_RATEMCS10:
		case ODM_RATEMCS9:
		case ODM_RATEMCS2:
		case ODM_RATEMCS1:
		case ODM_RATE18M:
		case ODM_RATE12M:
			rts_ini_rate = ODM_RATE12M;
			break;
		case ODM_RATEVHTSS3MCS0:
		case ODM_RATEVHTSS2MCS0:
		case ODM_RATEVHTSS1MCS0:
		case ODM_RATEMCS8:
		case ODM_RATEMCS0:
		case ODM_RATE9M:
		case ODM_RATE6M:
			rts_ini_rate = ODM_RATE6M;
			break;
		case ODM_RATE11M:
		case ODM_RATE5_5M:
		case ODM_RATE2M:
		case ODM_RATE1M:
			rts_ini_rate = ODM_RATE1M;
			break;
		default:
			rts_ini_rate = ODM_RATE6M;
			break;
		}
	}

	if (*dm->band_type == 1) {
		if (rts_ini_rate < ODM_RATE6M)
			rts_ini_rate = ODM_RATE6M;
	}
	return rts_ini_rate;
}