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
struct fb_info {scalar_t__ screen_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 

__attribute__((used)) static void mdpy_fb_destroy(struct fb_info *info)
{
	if (info->screen_base)
		iounmap(info->screen_base);
}