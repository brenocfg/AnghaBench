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
struct gs_sampler_info {int dummy; } ;
typedef  int /*<<< orphan*/  gs_samplerstate_t ;
struct TYPE_4__ {int /*<<< orphan*/ * (* device_samplerstate_create ) (int /*<<< orphan*/ ,struct gs_sampler_info const*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  device; TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid_p (char*,struct gs_sampler_info const*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ,struct gs_sampler_info const*) ; 
 TYPE_2__* thread_graphics ; 

gs_samplerstate_t *gs_samplerstate_create(const struct gs_sampler_info *info)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid_p("gs_samplerstate_create", info))
		return NULL;

	return graphics->exports.device_samplerstate_create(graphics->device,
							    info);
}