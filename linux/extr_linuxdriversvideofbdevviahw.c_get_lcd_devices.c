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
typedef  int u32 ;

/* Variables and functions */
#define  INTERFACE_DFP 135 
#define  INTERFACE_DFP_HIGH 134 
#define  INTERFACE_DFP_LOW 133 
#define  INTERFACE_DVP0 132 
#define  INTERFACE_DVP1 131 
#define  INTERFACE_LVDS0 130 
#define  INTERFACE_LVDS0LVDS1 129 
#define  INTERFACE_LVDS1 128 
 int VIA_DVP0 ; 
 int VIA_DVP1 ; 
 int VIA_LVDS1 ; 
 int VIA_LVDS2 ; 

__attribute__((used)) static u32 get_lcd_devices(int output_interface)
{
	switch (output_interface) {
	case INTERFACE_DVP0:
		return VIA_DVP0;

	case INTERFACE_DVP1:
		return VIA_DVP1;

	case INTERFACE_DFP_HIGH:
		return VIA_LVDS2 | VIA_DVP0;

	case INTERFACE_DFP_LOW:
		return VIA_LVDS1 | VIA_DVP1;

	case INTERFACE_DFP:
		return VIA_LVDS1 | VIA_LVDS2;

	case INTERFACE_LVDS0:
	case INTERFACE_LVDS0LVDS1:
		return VIA_LVDS1;

	case INTERFACE_LVDS1:
		return VIA_LVDS2;
	}

	return 0;
}