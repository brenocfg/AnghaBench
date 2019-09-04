#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  size_t u32 ;
struct TYPE_4__ {int physical; int offset; } ;
struct intelfb_info {int depth; size_t* pseudo_palette; int* cursor_src; TYPE_1__ cursor; scalar_t__ mobile; int /*<<< orphan*/  hwcursor; } ;
struct TYPE_5__ {size_t xoffset; size_t yoffset; } ;
struct fb_info {TYPE_2__ var; } ;
struct TYPE_6__ {int width; int height; size_t dx; size_t dy; size_t fg_color; size_t bg_color; int depth; scalar_t__ data; } ;
struct fb_cursor {int set; int rop; scalar_t__ enable; TYPE_3__ image; scalar_t__ mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_A_BASEADDR ; 
 int /*<<< orphan*/  DBG_MSG (char*,...) ; 
 int ENODEV ; 
 int ENXIO ; 
 int FB_CUR_SETCMAP ; 
 int FB_CUR_SETIMAGE ; 
 int FB_CUR_SETPOS ; 
 int FB_CUR_SETSHAPE ; 
 int FB_CUR_SETSIZE ; 
 struct intelfb_info* GET_DINFO (struct fb_info*) ; 
 size_t INREG (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_I9XX (struct intelfb_info*) ; 
#define  ROP_COPY 129 
#define  ROP_XOR 128 
 int ROUND_UP_TO (int,int) ; 
 int /*<<< orphan*/  intelfbhw_cursor_hide (struct intelfb_info*) ; 
 int /*<<< orphan*/  intelfbhw_cursor_init (struct intelfb_info*) ; 
 int /*<<< orphan*/  intelfbhw_cursor_load (struct intelfb_info*,int,int,int*) ; 
 int /*<<< orphan*/  intelfbhw_cursor_reset (struct intelfb_info*) ; 
 int /*<<< orphan*/  intelfbhw_cursor_setcolor (struct intelfb_info*,size_t,size_t) ; 
 int /*<<< orphan*/  intelfbhw_cursor_setpos (struct intelfb_info*,size_t,size_t) ; 
 int /*<<< orphan*/  intelfbhw_cursor_show (struct intelfb_info*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 

__attribute__((used)) static int intelfb_cursor(struct fb_info *info, struct fb_cursor *cursor)
{
        struct intelfb_info *dinfo = GET_DINFO(info);
	u32 physical;
#if VERBOSE > 0
	DBG_MSG("intelfb_cursor\n");
#endif

	if (!dinfo->hwcursor)
		return -ENODEV;

	intelfbhw_cursor_hide(dinfo);

	/* If XFree killed the cursor - restore it */
	physical = (dinfo->mobile || IS_I9XX(dinfo)) ? dinfo->cursor.physical :
		   (dinfo->cursor.offset << 12);

	if (INREG(CURSOR_A_BASEADDR) != physical) {
		u32 fg, bg;

		DBG_MSG("the cursor was killed - restore it !!\n");
		DBG_MSG("size %d, %d   pos %d, %d\n",
			cursor->image.width, cursor->image.height,
			cursor->image.dx, cursor->image.dy);

		intelfbhw_cursor_init(dinfo);
		intelfbhw_cursor_reset(dinfo);
		intelfbhw_cursor_setpos(dinfo, cursor->image.dx,
					cursor->image.dy);

		if (dinfo->depth != 8) {
			fg =dinfo->pseudo_palette[cursor->image.fg_color];
			bg =dinfo->pseudo_palette[cursor->image.bg_color];
		} else {
			fg = cursor->image.fg_color;
			bg = cursor->image.bg_color;
		}
		intelfbhw_cursor_setcolor(dinfo, bg, fg);
		intelfbhw_cursor_load(dinfo, cursor->image.width,
				      cursor->image.height,
				      dinfo->cursor_src);

		if (cursor->enable)
			intelfbhw_cursor_show(dinfo);
		return 0;
	}

	if (cursor->set & FB_CUR_SETPOS) {
		u32 dx, dy;

		dx = cursor->image.dx - info->var.xoffset;
		dy = cursor->image.dy - info->var.yoffset;

		intelfbhw_cursor_setpos(dinfo, dx, dy);
	}

	if (cursor->set & FB_CUR_SETSIZE) {
		if (cursor->image.width > 64 || cursor->image.height > 64)
			return -ENXIO;

		intelfbhw_cursor_reset(dinfo);
	}

	if (cursor->set & FB_CUR_SETCMAP) {
		u32 fg, bg;

		if (dinfo->depth != 8) {
			fg = dinfo->pseudo_palette[cursor->image.fg_color];
			bg = dinfo->pseudo_palette[cursor->image.bg_color];
		} else {
			fg = cursor->image.fg_color;
			bg = cursor->image.bg_color;
		}

		intelfbhw_cursor_setcolor(dinfo, bg, fg);
	}

	if (cursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) {
		u32 s_pitch = (ROUND_UP_TO(cursor->image.width, 8) / 8);
		u32 size = s_pitch * cursor->image.height;
		u8 *dat = (u8 *) cursor->image.data;
		u8 *msk = (u8 *) cursor->mask;
		u8 src[64];
		u32 i;

		if (cursor->image.depth != 1)
			return -ENXIO;

		switch (cursor->rop) {
		case ROP_XOR:
			for (i = 0; i < size; i++)
				src[i] = dat[i] ^ msk[i];
			break;
		case ROP_COPY:
		default:
			for (i = 0; i < size; i++)
				src[i] = dat[i] & msk[i];
			break;
		}

		/* save the bitmap to restore it when XFree will
		   make the cursor dirty */
		memcpy(dinfo->cursor_src, src, size);

		intelfbhw_cursor_load(dinfo, cursor->image.width,
				      cursor->image.height, src);
	}

	if (cursor->enable)
		intelfbhw_cursor_show(dinfo);

	return 0;
}