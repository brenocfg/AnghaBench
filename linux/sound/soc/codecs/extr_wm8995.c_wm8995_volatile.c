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
#define  WM8995_ACCESSORY_DETECT_MODE1 137 
#define  WM8995_ACCESSORY_DETECT_MODE2 136 
#define  WM8995_DC_SERVO_READBACK_0 135 
#define  WM8995_HEADPHONE_DETECT1 134 
#define  WM8995_HEADPHONE_DETECT2 133 
#define  WM8995_INTERRUPT_CONTROL 132 
#define  WM8995_INTERRUPT_STATUS_1 131 
#define  WM8995_INTERRUPT_STATUS_2 130 
#define  WM8995_RATE_STATUS 129 
#define  WM8995_SOFTWARE_RESET 128 

__attribute__((used)) static bool wm8995_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM8995_SOFTWARE_RESET:
	case WM8995_DC_SERVO_READBACK_0:
	case WM8995_INTERRUPT_STATUS_1:
	case WM8995_INTERRUPT_STATUS_2:
	case WM8995_INTERRUPT_CONTROL:
	case WM8995_ACCESSORY_DETECT_MODE1:
	case WM8995_ACCESSORY_DETECT_MODE2:
	case WM8995_HEADPHONE_DETECT1:
	case WM8995_HEADPHONE_DETECT2:
	case WM8995_RATE_STATUS:
		return true;
	default:
		return false;
	}
}