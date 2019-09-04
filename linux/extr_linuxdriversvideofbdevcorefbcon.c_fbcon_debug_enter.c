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
struct fbcon_ops {scalar_t__ graphics; scalar_t__ save_graphics; } ;
struct fb_info {TYPE_1__* fbops; struct fbcon_ops* fbcon_par; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fb_debug_enter ) (struct fb_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  color_table ; 
 size_t* con2fb_map ; 
 int /*<<< orphan*/  fbcon_set_palette (struct vc_data*,int /*<<< orphan*/ ) ; 
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  stub1 (struct fb_info*) ; 

__attribute__((used)) static int fbcon_debug_enter(struct vc_data *vc)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	struct fbcon_ops *ops = info->fbcon_par;

	ops->save_graphics = ops->graphics;
	ops->graphics = 0;
	if (info->fbops->fb_debug_enter)
		info->fbops->fb_debug_enter(info);
	fbcon_set_palette(vc, color_table);
	return 0;
}