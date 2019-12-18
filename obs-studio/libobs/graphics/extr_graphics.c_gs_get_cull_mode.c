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
struct TYPE_4__ {int (* device_get_cull_mode ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  device; TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;
typedef  enum gs_cull_mode { ____Placeholder_gs_cull_mode } gs_cull_mode ;

/* Variables and functions */
 int GS_NEITHER ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__* thread_graphics ; 

enum gs_cull_mode gs_get_cull_mode(void)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid("gs_get_cull_mode"))
		return GS_NEITHER;

	return graphics->exports.device_get_cull_mode(graphics->device);
}