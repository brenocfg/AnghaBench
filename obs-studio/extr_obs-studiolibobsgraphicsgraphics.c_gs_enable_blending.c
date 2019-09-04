#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* device_enable_blending ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {int enabled; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; TYPE_2__ exports; TYPE_1__ cur_blend_state; } ;
typedef  TYPE_3__ graphics_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* thread_graphics ; 

void gs_enable_blending(bool enable)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid("gs_enable_blending"))
		return;

	graphics->cur_blend_state.enabled = enable;
	graphics->exports.device_enable_blending(graphics->device, enable);
}