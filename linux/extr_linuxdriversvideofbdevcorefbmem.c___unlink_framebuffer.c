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
struct fb_info {int node; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FB_MAJOR ; 
 int FB_MAX ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_class ; 
 struct fb_info** registered_fb ; 

__attribute__((used)) static int __unlink_framebuffer(struct fb_info *fb_info)
{
	int i;

	i = fb_info->node;
	if (i < 0 || i >= FB_MAX || registered_fb[i] != fb_info)
		return -EINVAL;

	if (fb_info->dev) {
		device_destroy(fb_class, MKDEV(FB_MAJOR, i));
		fb_info->dev = NULL;
	}

	return 0;
}