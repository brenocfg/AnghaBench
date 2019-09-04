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
struct TYPE_3__ {scalar_t__ LVDSHDE; scalar_t__ LVDSVDE; } ;
struct xgifb_video_info {TYPE_1__ lvds_data; } ;
struct TYPE_4__ {scalar_t__ mode_no; scalar_t__ xres; scalar_t__ yres; int bpp; } ;

/* Variables and functions */
 TYPE_2__* XGIbios_mode ; 

__attribute__((used)) static int XGIfb_GetXG21DefaultLVDSModeIdx(struct xgifb_video_info *xgifb_info)
{
	int i = 0;

	while ((XGIbios_mode[i].mode_no != 0) &&
	       (XGIbios_mode[i].xres <= xgifb_info->lvds_data.LVDSHDE)) {
		if ((XGIbios_mode[i].xres == xgifb_info->lvds_data.LVDSHDE) &&
		    (XGIbios_mode[i].yres == xgifb_info->lvds_data.LVDSVDE) &&
		    (XGIbios_mode[i].bpp == 8)) {
			return i;
		}
		i++;
	}

	return -1;
}