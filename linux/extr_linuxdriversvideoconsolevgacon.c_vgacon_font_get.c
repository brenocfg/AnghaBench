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
struct TYPE_2__ {int /*<<< orphan*/  height; } ;
struct vc_data {TYPE_1__ vc_font; } ;
struct console_font {int charcount; int /*<<< orphan*/  data; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VGA_FONTWIDTH ; 
 scalar_t__ VIDEO_TYPE_EGAM ; 
 scalar_t__ vga_512_chars ; 
 scalar_t__ vga_video_type ; 
 int vgacon_do_font_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vgastate ; 

__attribute__((used)) static int vgacon_font_get(struct vc_data *c, struct console_font *font)
{
	if (vga_video_type < VIDEO_TYPE_EGAM)
		return -EINVAL;

	font->width = VGA_FONTWIDTH;
	font->height = c->vc_font.height;
	font->charcount = vga_512_chars ? 512 : 256;
	if (!font->data)
		return 0;
	return vgacon_do_font_op(&vgastate, font->data, 0, vga_512_chars);
}