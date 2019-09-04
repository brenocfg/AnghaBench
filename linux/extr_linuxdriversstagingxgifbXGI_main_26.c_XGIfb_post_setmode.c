#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct vb_device_info {int /*<<< orphan*/  Part2Port; int /*<<< orphan*/  Part1Port; int /*<<< orphan*/  Part4Port; int /*<<< orphan*/  P3c4; int /*<<< orphan*/  P3d4; } ;
struct xgifb_video_info {int video_bpp; scalar_t__ hasVB; scalar_t__ display2; int video_width; scalar_t__ TV_type; scalar_t__ TV_plug; struct vb_device_info dev_info; } ;
struct TYPE_2__ {int** filter; } ;

/* Variables and functions */
 scalar_t__ HASVB_301 ; 
 scalar_t__ HASVB_LVDS ; 
 scalar_t__ HASVB_LVDS_CHRONTEL ; 
 scalar_t__ HASVB_NONE ; 
 int IND_SIS_RAMDAC_CONTROL ; 
 int SIS_CRT2_WENABLE_315 ; 
 scalar_t__ TVMODE_NTSC ; 
 scalar_t__ TVMODE_PAL ; 
 scalar_t__ TVPLUG_COMPOSITE ; 
 scalar_t__ TVPLUG_SVIDEO ; 
 scalar_t__ XGIFB_DISP_LCD ; 
 scalar_t__ XGIFB_DISP_TV ; 
 TYPE_1__* XGI_TV_filter ; 
 scalar_t__ XGIfb_crt1off ; 
 int filter ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int const*) ; 
 int /*<<< orphan*/  xgifb_reg_and (int /*<<< orphan*/ ,int,int) ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgifb_reg_or (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xgifb_reg_set (int /*<<< orphan*/ ,int,int const) ; 

__attribute__((used)) static void XGIfb_post_setmode(struct xgifb_video_info *xgifb_info)
{
	struct vb_device_info *vb = &xgifb_info->dev_info;
	u8 reg;
	unsigned char doit = 1;

	if (xgifb_info->video_bpp == 8) {
		/*
		 * We can't switch off CRT1 on LVDS/Chrontel
		 * in 8bpp Modes
		 */
		if ((xgifb_info->hasVB == HASVB_LVDS) ||
		    (xgifb_info->hasVB == HASVB_LVDS_CHRONTEL)) {
			doit = 0;
		}
		/*
		 * We can't switch off CRT1 on 301B-DH
		 * in 8bpp Modes if using LCD
		 */
		if (xgifb_info->display2 == XGIFB_DISP_LCD)
			doit = 0;
	}

	/* We can't switch off CRT1 if bridge is in slave mode */
	if (xgifb_info->hasVB != HASVB_NONE) {
		reg = xgifb_reg_get(vb->Part1Port, 0x00);

		if ((reg & 0x50) == 0x10)
			doit = 0;

	} else {
		XGIfb_crt1off = 0;
	}

	reg = xgifb_reg_get(vb->P3d4, 0x17);
	if ((XGIfb_crt1off) && (doit))
		reg &= ~0x80;
	else
		reg |= 0x80;
	xgifb_reg_set(vb->P3d4, 0x17, reg);

	xgifb_reg_and(vb->P3c4, IND_SIS_RAMDAC_CONTROL, ~0x04);

	if (xgifb_info->display2 == XGIFB_DISP_TV &&
	    xgifb_info->hasVB == HASVB_301) {
		reg = xgifb_reg_get(vb->Part4Port, 0x01);

		if (reg < 0xB0) { /* Set filter for XGI301 */
			int filter_tb;

			switch (xgifb_info->video_width) {
			case 320:
				filter_tb = (xgifb_info->TV_type ==
					     TVMODE_NTSC) ? 4 : 12;
				break;
			case 640:
				filter_tb = (xgifb_info->TV_type ==
					     TVMODE_NTSC) ? 5 : 13;
				break;
			case 720:
				filter_tb = (xgifb_info->TV_type ==
					     TVMODE_NTSC) ? 6 : 14;
				break;
			case 800:
				filter_tb = (xgifb_info->TV_type ==
					     TVMODE_NTSC) ? 7 : 15;
				break;
			default:
				filter_tb = 0;
				filter = -1;
				break;
			}
			xgifb_reg_or(vb->Part1Port, SIS_CRT2_WENABLE_315, 0x01);

			if (xgifb_info->TV_type == TVMODE_NTSC) {
				xgifb_reg_and(vb->Part2Port, 0x3a, 0x1f);

				if (xgifb_info->TV_plug == TVPLUG_SVIDEO) {
					xgifb_reg_and(vb->Part2Port, 0x30, 0xdf);

				} else if (xgifb_info->TV_plug
						== TVPLUG_COMPOSITE) {
					xgifb_reg_or(vb->Part2Port, 0x30, 0x20);

					switch (xgifb_info->video_width) {
					case 640:
						xgifb_reg_set(vb->Part2Port,
							      0x35,
							      0xEB);
						xgifb_reg_set(vb->Part2Port,
							      0x36,
							      0x04);
						xgifb_reg_set(vb->Part2Port,
							      0x37,
							      0x25);
						xgifb_reg_set(vb->Part2Port,
							      0x38,
							      0x18);
						break;
					case 720:
						xgifb_reg_set(vb->Part2Port,
							      0x35,
							      0xEE);
						xgifb_reg_set(vb->Part2Port,
							      0x36,
							      0x0C);
						xgifb_reg_set(vb->Part2Port,
							      0x37,
							      0x22);
						xgifb_reg_set(vb->Part2Port,
							      0x38,
							      0x08);
						break;
					case 800:
						xgifb_reg_set(vb->Part2Port,
							      0x35,
							      0xEB);
						xgifb_reg_set(vb->Part2Port,
							      0x36,
							      0x15);
						xgifb_reg_set(vb->Part2Port,
							      0x37,
							      0x25);
						xgifb_reg_set(vb->Part2Port,
							      0x38,
							      0xF6);
						break;
					}
				}

			} else if (xgifb_info->TV_type == TVMODE_PAL) {
				xgifb_reg_and(vb->Part2Port, 0x3A, 0x1F);

				if (xgifb_info->TV_plug == TVPLUG_SVIDEO) {
					xgifb_reg_and(vb->Part2Port, 0x30, 0xDF);

				} else if (xgifb_info->TV_plug
						== TVPLUG_COMPOSITE) {
					xgifb_reg_or(vb->Part2Port, 0x30, 0x20);

					switch (xgifb_info->video_width) {
					case 640:
						xgifb_reg_set(vb->Part2Port,
							      0x35,
							      0xF1);
						xgifb_reg_set(vb->Part2Port,
							      0x36,
							      0xF7);
						xgifb_reg_set(vb->Part2Port,
							      0x37,
							      0x1F);
						xgifb_reg_set(vb->Part2Port,
							      0x38,
							      0x32);
						break;
					case 720:
						xgifb_reg_set(vb->Part2Port,
							      0x35,
							      0xF3);
						xgifb_reg_set(vb->Part2Port,
							      0x36,
							      0x00);
						xgifb_reg_set(vb->Part2Port,
							      0x37,
							      0x1D);
						xgifb_reg_set(vb->Part2Port,
							      0x38,
							      0x20);
						break;
					case 800:
						xgifb_reg_set(vb->Part2Port,
							      0x35,
							      0xFC);
						xgifb_reg_set(vb->Part2Port,
							      0x36,
							      0xFB);
						xgifb_reg_set(vb->Part2Port,
							      0x37,
							      0x14);
						xgifb_reg_set(vb->Part2Port,
							      0x38,
							      0x2A);
						break;
					}
				}
			}

			if ((filter >= 0) && (filter <= 7)) {
				const u8 *f = XGI_TV_filter[filter_tb].filter[filter];

				pr_debug("FilterTable[%d]-%d: %*ph\n",
					 filter_tb, filter, 4, f);
				xgifb_reg_set(vb->Part2Port, 0x35, f[0]);
				xgifb_reg_set(vb->Part2Port, 0x36, f[1]);
				xgifb_reg_set(vb->Part2Port, 0x37, f[2]);
				xgifb_reg_set(vb->Part2Port, 0x38, f[3]);
			}
		}
	}
}