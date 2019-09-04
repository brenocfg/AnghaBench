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
struct TYPE_2__ {int height; } ;
struct vc_data {scalar_t__ vc_mode; int vc_pos; int vc_cursor_type; TYPE_1__ vc_font; int /*<<< orphan*/  vc_x; } ;

/* Variables and functions */
#define  CM_DRAW 135 
#define  CM_ERASE 134 
#define  CM_MOVE 133 
#define  CUR_LOWER_HALF 132 
#define  CUR_LOWER_THIRD 131 
#define  CUR_NONE 130 
#define  CUR_TWO_THIRDS 129 
#define  CUR_UNDERLINE 128 
 scalar_t__ KD_TEXT ; 
 int /*<<< orphan*/  VIDEO_TYPE_VGAC ; 
 int /*<<< orphan*/  vga_video_type ; 
 int vga_vram_base ; 
 int /*<<< orphan*/  vgacon_restore_screen (struct vc_data*) ; 
 int /*<<< orphan*/  vgacon_set_cursor_size (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  write_vga (int,int) ; 

__attribute__((used)) static void vgacon_cursor(struct vc_data *c, int mode)
{
	if (c->vc_mode != KD_TEXT)
		return;

	vgacon_restore_screen(c);

	switch (mode) {
	case CM_ERASE:
		write_vga(14, (c->vc_pos - vga_vram_base) / 2);
	        if (vga_video_type >= VIDEO_TYPE_VGAC)
			vgacon_set_cursor_size(c->vc_x, 31, 30);
		else
			vgacon_set_cursor_size(c->vc_x, 31, 31);
		break;

	case CM_MOVE:
	case CM_DRAW:
		write_vga(14, (c->vc_pos - vga_vram_base) / 2);
		switch (c->vc_cursor_type & 0x0f) {
		case CUR_UNDERLINE:
			vgacon_set_cursor_size(c->vc_x,
					       c->vc_font.height -
					       (c->vc_font.height <
						10 ? 2 : 3),
					       c->vc_font.height -
					       (c->vc_font.height <
						10 ? 1 : 2));
			break;
		case CUR_TWO_THIRDS:
			vgacon_set_cursor_size(c->vc_x,
					       c->vc_font.height / 3,
					       c->vc_font.height -
					       (c->vc_font.height <
						10 ? 1 : 2));
			break;
		case CUR_LOWER_THIRD:
			vgacon_set_cursor_size(c->vc_x,
					       (c->vc_font.height * 2) / 3,
					       c->vc_font.height -
					       (c->vc_font.height <
						10 ? 1 : 2));
			break;
		case CUR_LOWER_HALF:
			vgacon_set_cursor_size(c->vc_x,
					       c->vc_font.height / 2,
					       c->vc_font.height -
					       (c->vc_font.height <
						10 ? 1 : 2));
			break;
		case CUR_NONE:
			if (vga_video_type >= VIDEO_TYPE_VGAC)
				vgacon_set_cursor_size(c->vc_x, 31, 30);
			else
				vgacon_set_cursor_size(c->vc_x, 31, 31);
			break;
		default:
			vgacon_set_cursor_size(c->vc_x, 1,
					       c->vc_font.height);
			break;
		}
		break;
	}
}