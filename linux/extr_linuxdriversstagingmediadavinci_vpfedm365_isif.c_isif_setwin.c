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
struct TYPE_2__ {int /*<<< orphan*/  base_addr; } ;
struct vpfe_isif_device {TYPE_1__ isif_cfg; } ;
struct v4l2_rect {int left; int width; int top; int height; } ;
typedef  enum isif_frmfmt { ____Placeholder_isif_frmfmt } isif_frmfmt ;

/* Variables and functions */
 int ISIF_FRMFMT_INTERLACED ; 
 int /*<<< orphan*/  LNH ; 
 int /*<<< orphan*/  LNV ; 
 int NUM_LINES_VER ; 
 int NUM_PX_HOR_MASK ; 
 int /*<<< orphan*/  SLV0 ; 
 int /*<<< orphan*/  SLV1 ; 
 int /*<<< orphan*/  SPH ; 
 int START_PX_HOR_MASK ; 
 int START_VER_ONE_MASK ; 
 int START_VER_TWO_MASK ; 
 int /*<<< orphan*/  VDINT0 ; 
 int /*<<< orphan*/  VDINT1 ; 
 int /*<<< orphan*/  isif_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isif_setwin(struct vpfe_isif_device *isif, struct v4l2_rect *image_win,
	    enum isif_frmfmt frm_fmt, int ppc, int mode)
{
	int horz_nr_pixels;
	int vert_nr_lines;
	int horz_start;
	int vert_start;
	int mid_img;

	/*
	 * ppc - per pixel count. indicates how many pixels per cell
	 * output to SDRAM. example, for ycbcr, it is one y and one c, so 2.
	 * raw capture this is 1
	 */
	horz_start = image_win->left << (ppc - 1);
	horz_nr_pixels = (image_win->width << (ppc - 1)) - 1;

	/* Writing the horizontal info into the registers */
	isif_write(isif->isif_cfg.base_addr,
		   horz_start & START_PX_HOR_MASK, SPH);
	isif_write(isif->isif_cfg.base_addr,
		   horz_nr_pixels & NUM_PX_HOR_MASK, LNH);
	vert_start = image_win->top;

	if (frm_fmt == ISIF_FRMFMT_INTERLACED) {
		vert_nr_lines = (image_win->height >> 1) - 1;
		vert_start >>= 1;
		/* To account for VD since line 0 doesn't have any data */
		vert_start += 1;
	} else {
		/* To account for VD since line 0 doesn't have any data */
		vert_start += 1;
		vert_nr_lines = image_win->height - 1;
		/* configure VDINT0 and VDINT1 */
		mid_img = vert_start + (image_win->height / 2);
		isif_write(isif->isif_cfg.base_addr, mid_img, VDINT1);
	}

	if (!mode)
		isif_write(isif->isif_cfg.base_addr, 0, VDINT0);
	else
		isif_write(isif->isif_cfg.base_addr, vert_nr_lines, VDINT0);
	isif_write(isif->isif_cfg.base_addr,
		   vert_start & START_VER_ONE_MASK, SLV0);
	isif_write(isif->isif_cfg.base_addr,
		   vert_start & START_VER_TWO_MASK, SLV1);
	isif_write(isif->isif_cfg.base_addr,
		   vert_nr_lines & NUM_LINES_VER, LNV);
}