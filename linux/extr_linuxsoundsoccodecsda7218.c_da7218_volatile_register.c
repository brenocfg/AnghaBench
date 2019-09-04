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
struct device {int dummy; } ;

/* Variables and functions */
#define  DA7218_ADC_MODE 143 
#define  DA7218_CALIB_CTRL 142 
#define  DA7218_CALIB_OFFSET_AUTO_M_1 141 
#define  DA7218_CALIB_OFFSET_AUTO_M_2 140 
#define  DA7218_CALIB_OFFSET_AUTO_U_1 139 
#define  DA7218_CALIB_OFFSET_AUTO_U_2 138 
#define  DA7218_EVENT 137 
#define  DA7218_EVENT_STATUS 136 
#define  DA7218_HPLDET_TEST 135 
#define  DA7218_HP_SNGL_CTRL 134 
#define  DA7218_PLL_REFOSC_CAL 133 
#define  DA7218_PLL_STATUS 132 
#define  DA7218_SOFT_RESET 131 
#define  DA7218_STATUS1 130 
#define  DA7218_SYSTEM_STATUS 129 
#define  DA7218_TONE_GEN_CFG1 128 

__attribute__((used)) static bool da7218_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case DA7218_STATUS1:
	case DA7218_SOFT_RESET:
	case DA7218_SYSTEM_STATUS:
	case DA7218_CALIB_CTRL:
	case DA7218_CALIB_OFFSET_AUTO_M_1:
	case DA7218_CALIB_OFFSET_AUTO_U_1:
	case DA7218_CALIB_OFFSET_AUTO_M_2:
	case DA7218_CALIB_OFFSET_AUTO_U_2:
	case DA7218_PLL_STATUS:
	case DA7218_PLL_REFOSC_CAL:
	case DA7218_TONE_GEN_CFG1:
	case DA7218_ADC_MODE:
	case DA7218_HP_SNGL_CTRL:
	case DA7218_HPLDET_TEST:
	case DA7218_EVENT_STATUS:
	case DA7218_EVENT:
		return true;
	default:
		return false;
	}
}