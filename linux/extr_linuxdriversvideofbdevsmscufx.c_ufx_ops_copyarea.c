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
struct ufx_data {int dummy; } ;
struct fb_info {struct ufx_data* par; } ;
struct fb_copyarea {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  sys_copyarea (struct fb_info*,struct fb_copyarea const*) ; 
 int /*<<< orphan*/  ufx_handle_damage (struct ufx_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ufx_ops_copyarea(struct fb_info *info,
				const struct fb_copyarea *area)
{

	struct ufx_data *dev = info->par;

	sys_copyarea(info, area);

	ufx_handle_damage(dev, area->dx, area->dy,
			area->width, area->height);
}