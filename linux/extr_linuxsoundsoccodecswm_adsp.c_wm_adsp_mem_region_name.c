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

/* Variables and functions */
#define  WMFW_ADSP1_DM 132 
#define  WMFW_ADSP1_PM 131 
#define  WMFW_ADSP1_ZM 130 
#define  WMFW_ADSP2_XM 129 
#define  WMFW_ADSP2_YM 128 

__attribute__((used)) static const char *wm_adsp_mem_region_name(unsigned int type)
{
	switch (type) {
	case WMFW_ADSP1_PM:
		return "PM";
	case WMFW_ADSP1_DM:
		return "DM";
	case WMFW_ADSP2_XM:
		return "XM";
	case WMFW_ADSP2_YM:
		return "YM";
	case WMFW_ADSP1_ZM:
		return "ZM";
	default:
		return NULL;
	}
}