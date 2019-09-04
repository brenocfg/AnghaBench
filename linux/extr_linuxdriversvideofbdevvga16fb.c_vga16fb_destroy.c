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
struct fb_info {int /*<<< orphan*/  cmap; int /*<<< orphan*/  screen_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_dealloc_cmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vga16fb_destroy(struct fb_info *info)
{
	iounmap(info->screen_base);
	fb_dealloc_cmap(&info->cmap);
	/* XXX unshare VGA regions */
	framebuffer_release(info);
}