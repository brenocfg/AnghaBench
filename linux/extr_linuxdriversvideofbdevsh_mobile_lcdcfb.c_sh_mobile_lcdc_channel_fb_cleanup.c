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
struct sh_mobile_lcdc_chan {int /*<<< orphan*/  sglist; struct fb_info* info; } ;
struct fb_info {int /*<<< orphan*/  cmap; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sh_mobile_lcdc_channel_fb_cleanup(struct sh_mobile_lcdc_chan *ch)
{
	struct fb_info *info = ch->info;

	if (!info || !info->device)
		return;

	vfree(ch->sglist);

	fb_dealloc_cmap(&info->cmap);
	framebuffer_release(info);
}