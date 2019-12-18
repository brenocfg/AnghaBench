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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vec4 {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* device_clear ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vec4 const*,float,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  device; TYPE_1__ exports; } ;
typedef  TYPE_2__ graphics_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vec4 const*,float,int /*<<< orphan*/ ) ; 
 TYPE_2__* thread_graphics ; 

void gs_clear(uint32_t clear_flags, const struct vec4 *color, float depth,
	      uint8_t stencil)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid("gs_clear"))
		return;

	graphics->exports.device_clear(graphics->device, clear_flags, color,
				       depth, stencil);
}