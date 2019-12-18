#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gs_init_data {int dummy; } ;
typedef  int /*<<< orphan*/  gs_swapchain_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* device_swapchain_create ) (int /*<<< orphan*/ ,struct gs_init_data*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  device; TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid_p (char*,struct gs_init_data const*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,struct gs_init_data*) ; 
 TYPE_2__* thread_graphics ; 

gs_swapchain_t *gs_swapchain_create(const struct gs_init_data *data)
{
	struct gs_init_data new_data = *data;
	graphics_t *graphics = thread_graphics;

	if (!gs_valid_p("gs_swapchain_create", data))
		return NULL;

	return graphics->exports.device_swapchain_create(graphics->device,
							 &new_data);
}