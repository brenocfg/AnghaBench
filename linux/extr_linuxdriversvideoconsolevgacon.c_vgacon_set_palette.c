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
struct vc_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ VIDEO_TYPE_VGAC ; 
 int /*<<< orphan*/  con_is_visible (struct vc_data*) ; 
 scalar_t__ vga_palette_blanked ; 
 int /*<<< orphan*/  vga_set_palette (struct vc_data*,unsigned char const*) ; 
 scalar_t__ vga_video_type ; 

__attribute__((used)) static void vgacon_set_palette(struct vc_data *vc, const unsigned char *table)
{
	if (vga_video_type != VIDEO_TYPE_VGAC || vga_palette_blanked
	    || !con_is_visible(vc))
		return;
	vga_set_palette(vc, table);
}