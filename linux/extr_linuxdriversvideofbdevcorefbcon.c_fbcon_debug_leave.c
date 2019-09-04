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
struct vc_data {size_t vc_num; } ;
struct fbcon_ops {int /*<<< orphan*/  save_graphics; int /*<<< orphan*/  graphics; } ;
struct fb_info {TYPE_1__* fbops; struct fbcon_ops* fbcon_par; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fb_debug_leave ) (struct fb_info*) ;} ;

/* Variables and functions */
 size_t* con2fb_map ; 
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 

__attribute__((used)) static int fbcon_debug_leave(struct vc_data *vc)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	struct fbcon_ops *ops = info->fbcon_par;

	ops->graphics = ops->save_graphics;
	if (info->fbops->fb_debug_leave)
		info->fbops->fb_debug_leave(info);
	return 0;
}