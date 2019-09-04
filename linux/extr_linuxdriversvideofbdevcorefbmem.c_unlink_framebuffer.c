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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int __unlink_framebuffer (struct fb_info*) ; 
 int /*<<< orphan*/  unbind_console (struct fb_info*) ; 

int unlink_framebuffer(struct fb_info *fb_info)
{
	int ret;

	ret = __unlink_framebuffer(fb_info);
	if (ret)
		return ret;

	unbind_console(fb_info);

	return 0;
}