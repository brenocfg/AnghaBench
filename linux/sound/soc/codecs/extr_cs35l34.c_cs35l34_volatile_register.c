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
#define  CS35L34_CLASS_H_STATUS 139 
#define  CS35L34_DEVID_AB 138 
#define  CS35L34_DEVID_CD 137 
#define  CS35L34_DEVID_E 136 
#define  CS35L34_FAB_ID 135 
#define  CS35L34_INT_STATUS_1 134 
#define  CS35L34_INT_STATUS_2 133 
#define  CS35L34_INT_STATUS_3 132 
#define  CS35L34_INT_STATUS_4 131 
#define  CS35L34_OTP_TRIM_STATUS 130 
#define  CS35L34_REV_ID 129 
#define  CS35L34_VPBR_ATTEN_STATUS 128 

__attribute__((used)) static bool cs35l34_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case CS35L34_DEVID_AB:
	case CS35L34_DEVID_CD:
	case CS35L34_DEVID_E:
	case CS35L34_FAB_ID:
	case CS35L34_REV_ID:
	case CS35L34_INT_STATUS_1:
	case CS35L34_INT_STATUS_2:
	case CS35L34_INT_STATUS_3:
	case CS35L34_INT_STATUS_4:
	case CS35L34_CLASS_H_STATUS:
	case CS35L34_VPBR_ATTEN_STATUS:
	case CS35L34_OTP_TRIM_STATUS:
		return true;
	default:
		return false;
	}
}