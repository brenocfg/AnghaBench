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
struct TYPE_3__ {unsigned int height; } ;
struct vc_data {TYPE_1__ vc_font; } ;
struct TYPE_4__ {unsigned int orig_video_cols; unsigned int orig_video_lines; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ con_is_visible (struct vc_data*) ; 
 TYPE_2__ screen_info ; 
 unsigned int vga_default_font_height ; 
 int /*<<< orphan*/  vga_is_gfx ; 
 int /*<<< orphan*/  vgacon_doresize (struct vc_data*,unsigned int,unsigned int) ; 

__attribute__((used)) static int vgacon_resize(struct vc_data *c, unsigned int width,
			 unsigned int height, unsigned int user)
{
	if (width % 2 || width > screen_info.orig_video_cols ||
	    height > (screen_info.orig_video_lines * vga_default_font_height)/
	    c->vc_font.height)
		/* let svgatextmode tinker with video timings and
		   return success */
		return (user) ? 0 : -EINVAL;

	if (con_is_visible(c) && !vga_is_gfx) /* who knows */
		vgacon_doresize(c, width, height);
	return 0;
}