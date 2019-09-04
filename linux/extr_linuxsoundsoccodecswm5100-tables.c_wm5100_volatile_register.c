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
#define  WM5100_DEVICE_REVISION 141 
 unsigned int WM5100_DSP1_DM_0 ; 
 unsigned int WM5100_DSP1_DM_511 ; 
 unsigned int WM5100_DSP1_PM_0 ; 
 unsigned int WM5100_DSP1_PM_1535 ; 
 unsigned int WM5100_DSP1_ZM_0 ; 
 unsigned int WM5100_DSP1_ZM_2047 ; 
 unsigned int WM5100_DSP2_DM_0 ; 
 unsigned int WM5100_DSP2_DM_511 ; 
 unsigned int WM5100_DSP2_PM_0 ; 
 unsigned int WM5100_DSP2_PM_1535 ; 
 unsigned int WM5100_DSP2_ZM_0 ; 
 unsigned int WM5100_DSP2_ZM_2047 ; 
 unsigned int WM5100_DSP3_DM_0 ; 
 unsigned int WM5100_DSP3_DM_511 ; 
 unsigned int WM5100_DSP3_PM_0 ; 
 unsigned int WM5100_DSP3_PM_1535 ; 
 unsigned int WM5100_DSP3_ZM_0 ; 
 unsigned int WM5100_DSP3_ZM_2047 ; 
#define  WM5100_FX_CTRL 140 
#define  WM5100_INPUT_ENABLES_STATUS 139 
#define  WM5100_INTERRUPT_RAW_STATUS_2 138 
#define  WM5100_INTERRUPT_RAW_STATUS_3 137 
#define  WM5100_INTERRUPT_RAW_STATUS_4 136 
#define  WM5100_INTERRUPT_STATUS_1 135 
#define  WM5100_INTERRUPT_STATUS_2 134 
#define  WM5100_INTERRUPT_STATUS_3 133 
#define  WM5100_INTERRUPT_STATUS_4 132 
#define  WM5100_MIC_DETECT_3 131 
#define  WM5100_OUTPUT_STATUS_1 130 
#define  WM5100_OUTPUT_STATUS_2 129 
#define  WM5100_SOFTWARE_RESET 128 

bool wm5100_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM5100_SOFTWARE_RESET:
	case WM5100_DEVICE_REVISION:
	case WM5100_FX_CTRL:
	case WM5100_INTERRUPT_STATUS_1:
	case WM5100_INTERRUPT_STATUS_2:
	case WM5100_INTERRUPT_STATUS_3:
	case WM5100_INTERRUPT_STATUS_4:
	case WM5100_INTERRUPT_RAW_STATUS_2:
	case WM5100_INTERRUPT_RAW_STATUS_3:
	case WM5100_INTERRUPT_RAW_STATUS_4:
	case WM5100_OUTPUT_STATUS_1:
	case WM5100_OUTPUT_STATUS_2:
	case WM5100_INPUT_ENABLES_STATUS:
	case WM5100_MIC_DETECT_3:
		return true;
	default:
		if ((reg >= WM5100_DSP1_PM_0 && reg <= WM5100_DSP1_PM_1535) ||
		    (reg >= WM5100_DSP1_ZM_0 && reg <= WM5100_DSP1_ZM_2047) ||
		    (reg >= WM5100_DSP1_DM_0 && reg <= WM5100_DSP1_DM_511) ||
		    (reg >= WM5100_DSP2_PM_0 && reg <= WM5100_DSP2_PM_1535) ||
		    (reg >= WM5100_DSP2_ZM_0 && reg <= WM5100_DSP2_ZM_2047) ||
		    (reg >= WM5100_DSP2_DM_0 && reg <= WM5100_DSP2_DM_511) ||
		    (reg >= WM5100_DSP3_PM_0 && reg <= WM5100_DSP3_PM_1535) ||
		    (reg >= WM5100_DSP3_ZM_0 && reg <= WM5100_DSP3_ZM_2047) ||
		    (reg >= WM5100_DSP3_DM_0 && reg <= WM5100_DSP3_DM_511))
			return true;
		else
			return false;
	}
}