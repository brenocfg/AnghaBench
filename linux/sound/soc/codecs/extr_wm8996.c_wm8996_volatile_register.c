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
#define  WM8996_CHIP_REVISION 142 
#define  WM8996_DC_SERVO_2 141 
#define  WM8996_DC_SERVO_6 140 
#define  WM8996_DC_SERVO_7 139 
#define  WM8996_DC_SERVO_READBACK_0 138 
#define  WM8996_FLL_CONTROL_6 137 
#define  WM8996_HEADPHONE_DETECT_1 136 
#define  WM8996_HEADPHONE_DETECT_2 135 
#define  WM8996_INTERRUPT_RAW_STATUS_2 134 
#define  WM8996_INTERRUPT_STATUS_1 133 
#define  WM8996_INTERRUPT_STATUS_2 132 
#define  WM8996_LDO_1 131 
#define  WM8996_LDO_2 130 
#define  WM8996_MIC_DETECT_3 129 
#define  WM8996_SOFTWARE_RESET 128 

__attribute__((used)) static bool wm8996_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM8996_SOFTWARE_RESET:
	case WM8996_CHIP_REVISION:
	case WM8996_LDO_1:
	case WM8996_LDO_2:
	case WM8996_INTERRUPT_STATUS_1:
	case WM8996_INTERRUPT_STATUS_2:
	case WM8996_INTERRUPT_RAW_STATUS_2:
	case WM8996_DC_SERVO_READBACK_0:
	case WM8996_DC_SERVO_2:
	case WM8996_DC_SERVO_6:
	case WM8996_DC_SERVO_7:
	case WM8996_FLL_CONTROL_6:
	case WM8996_MIC_DETECT_3:
	case WM8996_HEADPHONE_DETECT_1:
	case WM8996_HEADPHONE_DETECT_2:
		return true;
	default:
		return false;
	}
}