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
typedef  enum radio_path { ____Placeholder_radio_path } radio_path ;

/* Variables and functions */
#define  DESC92C_RATE11M 155 
#define  DESC92C_RATE12M 154 
#define  DESC92C_RATE18M 153 
#define  DESC92C_RATE1M 152 
#define  DESC92C_RATE24M 151 
#define  DESC92C_RATE2M 150 
#define  DESC92C_RATE36M 149 
#define  DESC92C_RATE48M 148 
#define  DESC92C_RATE54M 147 
#define  DESC92C_RATE5_5M 146 
#define  DESC92C_RATE6M 145 
#define  DESC92C_RATE9M 144 
#define  DESC92C_RATEMCS0 143 
#define  DESC92C_RATEMCS1 142 
#define  DESC92C_RATEMCS10 141 
#define  DESC92C_RATEMCS11 140 
#define  DESC92C_RATEMCS12 139 
#define  DESC92C_RATEMCS13 138 
#define  DESC92C_RATEMCS14 137 
#define  DESC92C_RATEMCS15 136 
#define  DESC92C_RATEMCS2 135 
#define  DESC92C_RATEMCS3 134 
#define  DESC92C_RATEMCS4 133 
#define  DESC92C_RATEMCS5 132 
#define  DESC92C_RATEMCS6 131 
#define  DESC92C_RATEMCS7 130 
#define  DESC92C_RATEMCS8 129 
#define  DESC92C_RATEMCS9 128 
 int RF90_PATH_A ; 
 int RF90_PATH_B ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 

__attribute__((used)) static u8 _rtl92ee_phy_get_ratesection_intxpower_byrate(enum radio_path path,
							u8 rate)
{
	u8 rate_section = 0;

	switch (rate) {
	case DESC92C_RATE1M:
		rate_section = 2;
		break;
	case DESC92C_RATE2M:
	case DESC92C_RATE5_5M:
		if (path == RF90_PATH_A)
			rate_section = 3;
		else if (path == RF90_PATH_B)
			rate_section = 2;
		break;
	case DESC92C_RATE11M:
		rate_section = 3;
		break;
	case DESC92C_RATE6M:
	case DESC92C_RATE9M:
	case DESC92C_RATE12M:
	case DESC92C_RATE18M:
		rate_section = 0;
		break;
	case DESC92C_RATE24M:
	case DESC92C_RATE36M:
	case DESC92C_RATE48M:
	case DESC92C_RATE54M:
		rate_section = 1;
		break;
	case DESC92C_RATEMCS0:
	case DESC92C_RATEMCS1:
	case DESC92C_RATEMCS2:
	case DESC92C_RATEMCS3:
		rate_section = 4;
		break;
	case DESC92C_RATEMCS4:
	case DESC92C_RATEMCS5:
	case DESC92C_RATEMCS6:
	case DESC92C_RATEMCS7:
		rate_section = 5;
		break;
	case DESC92C_RATEMCS8:
	case DESC92C_RATEMCS9:
	case DESC92C_RATEMCS10:
	case DESC92C_RATEMCS11:
		rate_section = 6;
		break;
	case DESC92C_RATEMCS12:
	case DESC92C_RATEMCS13:
	case DESC92C_RATEMCS14:
	case DESC92C_RATEMCS15:
		rate_section = 7;
		break;
	default:
		WARN_ONCE(true, "rtl8192ee: Rate_Section is Illegal\n");
		break;
	}
	return rate_section;
}