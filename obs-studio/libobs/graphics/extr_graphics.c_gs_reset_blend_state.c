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
struct TYPE_4__ {scalar_t__ src_c; scalar_t__ dest_c; scalar_t__ src_a; scalar_t__ dest_a; int /*<<< orphan*/  enabled; } ;
struct TYPE_5__ {TYPE_1__ cur_blend_state; } ;
typedef  TYPE_2__ graphics_t ;

/* Variables and functions */
 scalar_t__ GS_BLEND_INVSRCALPHA ; 
 scalar_t__ GS_BLEND_ONE ; 
 scalar_t__ GS_BLEND_SRCALPHA ; 
 int /*<<< orphan*/  gs_blend_function_separate (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gs_enable_blending (int) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 TYPE_2__* thread_graphics ; 

void gs_reset_blend_state(void)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid("gs_preprocessor_name"))
		return;

	if (!graphics->cur_blend_state.enabled)
		gs_enable_blending(true);

	if (graphics->cur_blend_state.src_c != GS_BLEND_SRCALPHA ||
	    graphics->cur_blend_state.dest_c != GS_BLEND_INVSRCALPHA ||
	    graphics->cur_blend_state.src_a != GS_BLEND_ONE ||
	    graphics->cur_blend_state.dest_a != GS_BLEND_INVSRCALPHA)
		gs_blend_function_separate(GS_BLEND_SRCALPHA,
					   GS_BLEND_INVSRCALPHA, GS_BLEND_ONE,
					   GS_BLEND_INVSRCALPHA);
}