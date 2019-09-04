#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* chip_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  gfx_chip_name; } ;

/* Variables and functions */
#define  INTERFACE_DFP_HIGH 132 
#define  INTERFACE_DFP_LOW 131 
#define  INTERFACE_DVP0 130 
#define  INTERFACE_DVP1 129 
#define  INTERFACE_TMDS 128 
 int /*<<< orphan*/  UNICHROME_CLE266 ; 
 int VIA_DVP0 ; 
 int VIA_DVP1 ; 
 int VIA_LDVP0 ; 
 int VIA_LDVP1 ; 
 int VIA_LVDS1 ; 
 int VIA_LVDS2 ; 
 TYPE_2__* viaparinfo ; 

__attribute__((used)) static u32 get_dvi_devices(int output_interface)
{
	switch (output_interface) {
	case INTERFACE_DVP0:
		return VIA_DVP0 | VIA_LDVP0;

	case INTERFACE_DVP1:
		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
			return VIA_LDVP1;
		else
			return VIA_DVP1;

	case INTERFACE_DFP_HIGH:
		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
			return 0;
		else
			return VIA_LVDS2 | VIA_DVP0;

	case INTERFACE_DFP_LOW:
		if (viaparinfo->chip_info->gfx_chip_name == UNICHROME_CLE266)
			return 0;
		else
			return VIA_DVP1 | VIA_LVDS1;

	case INTERFACE_TMDS:
		return VIA_LVDS1;
	}

	return 0;
}