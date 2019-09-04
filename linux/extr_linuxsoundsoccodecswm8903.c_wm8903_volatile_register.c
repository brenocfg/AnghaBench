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
#define  WM8903_DC_SERVO_READBACK_1 135 
#define  WM8903_DC_SERVO_READBACK_2 134 
#define  WM8903_DC_SERVO_READBACK_3 133 
#define  WM8903_DC_SERVO_READBACK_4 132 
#define  WM8903_INTERRUPT_STATUS_1 131 
#define  WM8903_REVISION_NUMBER 130 
#define  WM8903_SW_RESET_AND_ID 129 
#define  WM8903_WRITE_SEQUENCER_4 128 

__attribute__((used)) static bool wm8903_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM8903_SW_RESET_AND_ID:
	case WM8903_REVISION_NUMBER:
	case WM8903_INTERRUPT_STATUS_1:
	case WM8903_WRITE_SEQUENCER_4:
	case WM8903_DC_SERVO_READBACK_1:
	case WM8903_DC_SERVO_READBACK_2:
	case WM8903_DC_SERVO_READBACK_3:
	case WM8903_DC_SERVO_READBACK_4:
		return true;

	default:
		return false;
	}
}