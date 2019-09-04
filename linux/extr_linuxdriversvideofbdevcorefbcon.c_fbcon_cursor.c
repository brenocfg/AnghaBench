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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {size_t vc_num; int vc_deccm; int vc_cursor_type; int /*<<< orphan*/  vc_cur_blink_ms; scalar_t__ vc_pos; } ;
struct fbcon_ops {int cursor_flash; int /*<<< orphan*/  (* cursor ) (struct vc_data*,struct fb_info*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  cur_blink_jiffies; } ;
struct fb_info {struct fbcon_ops* fbcon_par; } ;

/* Variables and functions */
 int CM_ERASE ; 
 int CM_SOFTBACK ; 
 size_t* con2fb_map ; 
 int /*<<< orphan*/  fbcon_add_cursor_timer (struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_del_cursor_timer (struct fb_info*) ; 
 scalar_t__ fbcon_is_inactive (struct vc_data*,struct fb_info*) ; 
 int /*<<< orphan*/  fbcon_set_origin (struct vc_data*) ; 
 int /*<<< orphan*/  get_color (struct vc_data*,struct fb_info*,int,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct fb_info** registered_fb ; 
 int scr_readw (int /*<<< orphan*/ *) ; 
 int softback_lines ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,struct fb_info*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fbcon_cursor(struct vc_data *vc, int mode)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	struct fbcon_ops *ops = info->fbcon_par;
	int y;
 	int c = scr_readw((u16 *) vc->vc_pos);

	ops->cur_blink_jiffies = msecs_to_jiffies(vc->vc_cur_blink_ms);

	if (fbcon_is_inactive(vc, info) || vc->vc_deccm != 1)
		return;

	if (vc->vc_cursor_type & 0x10)
		fbcon_del_cursor_timer(info);
	else
		fbcon_add_cursor_timer(info);

	ops->cursor_flash = (mode == CM_ERASE) ? 0 : 1;
	if (mode & CM_SOFTBACK) {
		mode &= ~CM_SOFTBACK;
		y = softback_lines;
	} else {
		if (softback_lines)
			fbcon_set_origin(vc);
		y = 0;
	}

	ops->cursor(vc, info, mode, y, get_color(vc, info, c, 1),
		    get_color(vc, info, c, 0));
}