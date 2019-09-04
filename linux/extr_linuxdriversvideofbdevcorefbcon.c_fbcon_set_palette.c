#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct vc_data {size_t vc_num; int* vc_palette; } ;
struct fb_info {int /*<<< orphan*/  fix; int /*<<< orphan*/  var; } ;
struct TYPE_4__ {int len; scalar_t__ start; } ;

/* Variables and functions */
 size_t* con2fb_map ; 
 int /*<<< orphan*/  con_is_visible (struct vc_data*) ; 
 int /*<<< orphan*/  fb_copy_cmap (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  fb_default_cmap (int) ; 
 int fb_get_color_depth (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_set_cmap (TYPE_1__*,struct fb_info*) ; 
 scalar_t__ fbcon_is_inactive (struct vc_data*,struct fb_info*) ; 
 int* palette_blue ; 
 TYPE_1__ palette_cmap ; 
 int* palette_green ; 
 int* palette_red ; 
 struct fb_info** registered_fb ; 

__attribute__((used)) static void fbcon_set_palette(struct vc_data *vc, const unsigned char *table)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	int i, j, k, depth;
	u8 val;

	if (fbcon_is_inactive(vc, info))
		return;

	if (!con_is_visible(vc))
		return;

	depth = fb_get_color_depth(&info->var, &info->fix);
	if (depth > 3) {
		for (i = j = 0; i < 16; i++) {
			k = table[i];
			val = vc->vc_palette[j++];
			palette_red[k] = (val << 8) | val;
			val = vc->vc_palette[j++];
			palette_green[k] = (val << 8) | val;
			val = vc->vc_palette[j++];
			palette_blue[k] = (val << 8) | val;
		}
		palette_cmap.len = 16;
		palette_cmap.start = 0;
	/*
	 * If framebuffer is capable of less than 16 colors,
	 * use default palette of fbcon.
	 */
	} else
		fb_copy_cmap(fb_default_cmap(1 << depth), &palette_cmap);

	fb_set_cmap(&palette_cmap, info);
}