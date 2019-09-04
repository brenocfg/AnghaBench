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
typedef  enum wl18xx_rdl_num { ____Placeholder_wl18xx_rdl_num } wl18xx_rdl_num ;

/* Variables and functions */
#define  RDL_1_HP 136 
#define  RDL_2_SP 135 
#define  RDL_3_HP 134 
#define  RDL_4_SP 133 
#define  RDL_5_SP 132 
#define  RDL_6_SP 131 
#define  RDL_7_SP 130 
#define  RDL_8_SP 129 
#define  RDL_NONE 128 

__attribute__((used)) static const char *wl18xx_rdl_name(enum wl18xx_rdl_num rdl_num)
{
	switch (rdl_num) {
	case RDL_1_HP:
		return "183xH";
	case RDL_2_SP:
		return "183x or 180x";
	case RDL_3_HP:
		return "187xH";
	case RDL_4_SP:
		return "187x";
	case RDL_5_SP:
		return "RDL11 - Not Supported";
	case RDL_6_SP:
		return "180xD";
	case RDL_7_SP:
		return "RDL13 - Not Supported (1893Q)";
	case RDL_8_SP:
		return "18xxQ";
	case RDL_NONE:
		return "UNTRIMMED";
	default:
		return "UNKNOWN";
	}
}