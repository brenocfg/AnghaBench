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
struct console_font {unsigned int charcount; scalar_t__ width; int /*<<< orphan*/  height; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int KD_FONT_FLAG_DONT_RECALC ; 
 scalar_t__ VGA_FONTWIDTH ; 
 scalar_t__ VIDEO_TYPE_EGAM ; 
 scalar_t__ vga_video_type ; 
 int vgacon_adjust_height (struct vc_data*,int /*<<< orphan*/ ) ; 
 int vgacon_do_font_op (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vgastate ; 

__attribute__((used)) static int vgacon_font_set(struct vc_data *c, struct console_font *font,
			   unsigned int flags)
{
	unsigned charcount = font->charcount;
	int rc;

	if (vga_video_type < VIDEO_TYPE_EGAM)
		return -EINVAL;

	if (font->width != VGA_FONTWIDTH ||
	    (charcount != 256 && charcount != 512))
		return -EINVAL;

	rc = vgacon_do_font_op(&vgastate, font->data, 1, charcount == 512);
	if (rc)
		return rc;

	if (!(flags & KD_FONT_FLAG_DONT_RECALC))
		rc = vgacon_adjust_height(c, font->height);
	return rc;
}