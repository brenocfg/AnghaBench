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
typedef  int u32 ;

/* Variables and functions */
#define  RTXAGC_A_CCK1_MCS32 142 
#define  RTXAGC_A_MCS03_MCS00 141 
#define  RTXAGC_A_MCS07_MCS04 140 
#define  RTXAGC_A_MCS11_MCS08 139 
#define  RTXAGC_A_MCS15_MCS12 138 
#define  RTXAGC_A_RATE18_06 137 
#define  RTXAGC_A_RATE54_24 136 
#define  RTXAGC_B_CCK11_A_CCK2_11 135 
#define  RTXAGC_B_CCK1_55_MCS32 134 
#define  RTXAGC_B_MCS03_MCS00 133 
#define  RTXAGC_B_MCS07_MCS04 132 
#define  RTXAGC_B_MCS11_MCS08 131 
#define  RTXAGC_B_MCS15_MCS12 130 
#define  RTXAGC_B_RATE18_06 129 
#define  RTXAGC_B_RATE54_24 128 

__attribute__((used)) static u8 _rtl8723be_get_rate_section_index(u32 regaddr)
{
	u8 index = 0;

	switch (regaddr) {
	case RTXAGC_A_RATE18_06:
		index = 0;
	break;
	case RTXAGC_A_RATE54_24:
		index = 1;
	break;
	case RTXAGC_A_CCK1_MCS32:
		index = 2;
	break;
	case RTXAGC_B_CCK11_A_CCK2_11:
		index = 3;
	break;
	case RTXAGC_A_MCS03_MCS00:
		index = 4;
	break;
	case RTXAGC_A_MCS07_MCS04:
		index = 5;
	break;
	case RTXAGC_A_MCS11_MCS08:
		index = 6;
	break;
	case RTXAGC_A_MCS15_MCS12:
		index = 7;
	break;
	case RTXAGC_B_RATE18_06:
		index = 0;
	break;
	case RTXAGC_B_RATE54_24:
		index = 1;
	break;
	case RTXAGC_B_CCK1_55_MCS32:
		index = 2;
	break;
	case RTXAGC_B_MCS03_MCS00:
		index = 4;
	break;
	case RTXAGC_B_MCS07_MCS04:
		index = 5;
	break;
	case RTXAGC_B_MCS11_MCS08:
		index = 6;
	break;
	case RTXAGC_B_MCS15_MCS12:
		index = 7;
	break;
	default:
		regaddr &= 0xFFF;
		if (regaddr >= 0xC20 && regaddr <= 0xC4C)
			index = (u8)((regaddr - 0xC20) / 4);
		else if (regaddr >= 0xE20 && regaddr <= 0xE4C)
			index = (u8)((regaddr - 0xE20) / 4);
		break;
	};
	return index;
}