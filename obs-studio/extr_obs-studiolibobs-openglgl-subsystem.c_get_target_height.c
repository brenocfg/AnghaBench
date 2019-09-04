#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct gs_device {TYPE_1__* cur_render_target; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ GS_TEXTURE_2D ; 
 int /*<<< orphan*/  device_get_height (struct gs_device const*) ; 
 int /*<<< orphan*/  gs_cubetexture_get_size (TYPE_1__*) ; 
 int /*<<< orphan*/  gs_texture_get_height (TYPE_1__*) ; 

__attribute__((used)) static inline uint32_t get_target_height(const struct gs_device *device)
{
	if (!device->cur_render_target)
		return device_get_height(device);

	if (device->cur_render_target->type == GS_TEXTURE_2D)
		return gs_texture_get_height(device->cur_render_target);
	else /* cube map */
		return gs_cubetexture_get_size(device->cur_render_target);
}