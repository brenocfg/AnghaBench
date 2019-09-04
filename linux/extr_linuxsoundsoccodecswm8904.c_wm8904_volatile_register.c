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
#define  WM8904_DC_SERVO_1 136 
#define  WM8904_DC_SERVO_6 135 
#define  WM8904_DC_SERVO_7 134 
#define  WM8904_DC_SERVO_8 133 
#define  WM8904_DC_SERVO_9 132 
#define  WM8904_DC_SERVO_READBACK_0 131 
#define  WM8904_INTERRUPT_STATUS 130 
#define  WM8904_REVISION 129 
#define  WM8904_SW_RESET_AND_ID 128 

__attribute__((used)) static bool wm8904_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM8904_SW_RESET_AND_ID:
	case WM8904_REVISION:
	case WM8904_DC_SERVO_1:
	case WM8904_DC_SERVO_6:
	case WM8904_DC_SERVO_7:
	case WM8904_DC_SERVO_8:
	case WM8904_DC_SERVO_9:
	case WM8904_DC_SERVO_READBACK_0:
	case WM8904_INTERRUPT_STATUS:
		return true;
	default:
		return false;
	}
}