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
struct vc_data {size_t vc_num; } ;
struct font_desc {int /*<<< orphan*/  data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {int /*<<< orphan*/  blit_y; int /*<<< orphan*/  blit_x; } ;
struct TYPE_3__ {int /*<<< orphan*/  yres; int /*<<< orphan*/  xres; } ;
struct fb_info {TYPE_2__ pixmap; TYPE_1__ var; } ;
struct console_font {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int ENOENT ; 
 size_t* con2fb_map ; 
 int fbcon_do_set_font (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct font_desc* find_font (char*) ; 
 struct font_desc* get_default_font (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fb_info** registered_fb ; 

__attribute__((used)) static int fbcon_set_def_font(struct vc_data *vc, struct console_font *font, char *name)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	const struct font_desc *f;

	if (!name)
		f = get_default_font(info->var.xres, info->var.yres,
				     info->pixmap.blit_x, info->pixmap.blit_y);
	else if (!(f = find_font(name)))
		return -ENOENT;

	font->width = f->width;
	font->height = f->height;
	return fbcon_do_set_font(vc, f->width, f->height, f->data, 0);
}