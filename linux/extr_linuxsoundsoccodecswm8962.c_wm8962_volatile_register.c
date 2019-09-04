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
#define  WM8962_ADDITIONAL_CONTROL_4 136 
#define  WM8962_CLOCKING1 135 
#define  WM8962_CLOCKING2 134 
#define  WM8962_DC_SERVO_6 133 
#define  WM8962_DSP2_EXECCONTROL 132 
#define  WM8962_INTERRUPT_STATUS_1 131 
#define  WM8962_INTERRUPT_STATUS_2 130 
#define  WM8962_SOFTWARE_RESET 129 
#define  WM8962_THERMAL_SHUTDOWN_STATUS 128 

__attribute__((used)) static bool wm8962_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM8962_CLOCKING1:
	case WM8962_CLOCKING2:
	case WM8962_SOFTWARE_RESET:
	case WM8962_THERMAL_SHUTDOWN_STATUS:
	case WM8962_ADDITIONAL_CONTROL_4:
	case WM8962_DC_SERVO_6:
	case WM8962_INTERRUPT_STATUS_1:
	case WM8962_INTERRUPT_STATUS_2:
	case WM8962_DSP2_EXECCONTROL:
		return true;
	default:
		return false;
	}
}