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
typedef  unsigned int u8 ;
typedef  unsigned int u16 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DSSDBG (char*,unsigned int,unsigned int) ; 
#define  OMAP_DSS_COLOR_CLUT1 131 
#define  OMAP_DSS_COLOR_CLUT2 130 
#define  OMAP_DSS_COLOR_CLUT4 129 
#define  OMAP_DSS_COLOR_CLUT8 128 
 int OMAP_DSS_COLOR_UYVY ; 
 int OMAP_DSS_COLOR_YUV2 ; 
 int color_mode_to_bpp (int) ; 
 int /*<<< orphan*/  pixinc (int,unsigned int) ; 

__attribute__((used)) static void calc_tiler_rotation_offset(u16 screen_width, u16 width,
		enum omap_color_mode color_mode, bool fieldmode,
		unsigned int field_offset, unsigned *offset0, unsigned *offset1,
		s32 *row_inc, s32 *pix_inc, int x_predecim, int y_predecim)
{
	u8 ps;

	switch (color_mode) {
	case OMAP_DSS_COLOR_CLUT1:
	case OMAP_DSS_COLOR_CLUT2:
	case OMAP_DSS_COLOR_CLUT4:
	case OMAP_DSS_COLOR_CLUT8:
		BUG();
		return;
	default:
		ps = color_mode_to_bpp(color_mode) / 8;
		break;
	}

	DSSDBG("scrw %d, width %d\n", screen_width, width);

	/*
	 * field 0 = even field = bottom field
	 * field 1 = odd field = top field
	 */
	*offset1 = 0;
	if (field_offset)
		*offset0 = *offset1 + field_offset * screen_width * ps;
	else
		*offset0 = *offset1;
	*row_inc = pixinc(1 + (y_predecim * screen_width - width * x_predecim) +
			(fieldmode ? screen_width : 0), ps);
	if (color_mode == OMAP_DSS_COLOR_YUV2 ||
		color_mode == OMAP_DSS_COLOR_UYVY)
		*pix_inc = pixinc(x_predecim, 2 * ps);
	else
		*pix_inc = pixinc(x_predecim, ps);
}