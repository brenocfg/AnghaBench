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
struct vc_data {int vc_cursor_type; int /*<<< orphan*/  vc_y; int /*<<< orphan*/  vc_x; } ;
struct fb_tilecursor {int mode; int fg; int bg; int /*<<< orphan*/  shape; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; } ;
struct fb_info {TYPE_1__* tileops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fb_tilecursor ) (struct fb_info*,struct fb_tilecursor*) ;} ;

/* Variables and functions */
 int CM_ERASE ; 
#define  CUR_BLOCK 133 
#define  CUR_LOWER_HALF 132 
#define  CUR_LOWER_THIRD 131 
#define  CUR_NONE 130 
#define  CUR_TWO_THIRDS 129 
#define  CUR_UNDERLINE 128 
 int /*<<< orphan*/  FB_TILE_CURSOR_BLOCK ; 
 int /*<<< orphan*/  FB_TILE_CURSOR_LOWER_HALF ; 
 int /*<<< orphan*/  FB_TILE_CURSOR_LOWER_THIRD ; 
 int /*<<< orphan*/  FB_TILE_CURSOR_NONE ; 
 int /*<<< orphan*/  FB_TILE_CURSOR_TWO_THIRDS ; 
 int /*<<< orphan*/  FB_TILE_CURSOR_UNDERLINE ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_tilecursor*) ; 

__attribute__((used)) static void tile_cursor(struct vc_data *vc, struct fb_info *info, int mode,
			int softback_lines, int fg, int bg)
{
	struct fb_tilecursor cursor;
	int use_sw = (vc->vc_cursor_type & 0x10);

	cursor.sx = vc->vc_x;
	cursor.sy = vc->vc_y;
	cursor.mode = (mode == CM_ERASE || use_sw) ? 0 : 1;
	cursor.fg = fg;
	cursor.bg = bg;

	switch (vc->vc_cursor_type & 0x0f) {
	case CUR_NONE:
		cursor.shape = FB_TILE_CURSOR_NONE;
		break;
	case CUR_UNDERLINE:
		cursor.shape = FB_TILE_CURSOR_UNDERLINE;
		break;
	case CUR_LOWER_THIRD:
		cursor.shape = FB_TILE_CURSOR_LOWER_THIRD;
		break;
	case CUR_LOWER_HALF:
		cursor.shape = FB_TILE_CURSOR_LOWER_HALF;
		break;
	case CUR_TWO_THIRDS:
		cursor.shape = FB_TILE_CURSOR_TWO_THIRDS;
		break;
	case CUR_BLOCK:
	default:
		cursor.shape = FB_TILE_CURSOR_BLOCK;
		break;
	}

	info->tileops->fb_tilecursor(info, &cursor);
}