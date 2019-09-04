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
struct fbcon_ops {int /*<<< orphan*/  rotate; } ;
struct fb_info {struct fbcon_ops* fbcon_par; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_ROTATE_UR ; 

__attribute__((used)) static inline void fbcon_set_rotation(struct fb_info *info)
{
	struct fbcon_ops *ops = info->fbcon_par;

	ops->rotate = FB_ROTATE_UR;
}