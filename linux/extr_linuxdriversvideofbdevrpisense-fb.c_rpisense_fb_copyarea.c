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
struct fb_info {int /*<<< orphan*/  deferred_work; } ;
struct fb_copyarea {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  delay; } ;

/* Variables and functions */
 TYPE_1__ rpisense_fb_defio ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_copyarea (struct fb_info*,struct fb_copyarea const*) ; 

__attribute__((used)) static void rpisense_fb_copyarea(struct fb_info *info,
				 const struct fb_copyarea *area)
{
	sys_copyarea(info, area);
	schedule_delayed_work(&info->deferred_work, rpisense_fb_defio.delay);
}