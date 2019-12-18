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
struct TYPE_6__ {int /*<<< orphan*/  (* device_blend_function ) (int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_5__ {int src_c; int dest_c; int src_a; int dest_a; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; TYPE_2__ exports; TYPE_1__ cur_blend_state; } ;
typedef  TYPE_3__ graphics_t ;
typedef  enum gs_blend_type { ____Placeholder_gs_blend_type } gs_blend_type ;

/* Variables and functions */
 int /*<<< orphan*/  gs_valid (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* thread_graphics ; 

void gs_blend_function(enum gs_blend_type src, enum gs_blend_type dest)
{
	graphics_t *graphics = thread_graphics;

	if (!gs_valid("gs_blend_function"))
		return;

	graphics->cur_blend_state.src_c = src;
	graphics->cur_blend_state.dest_c = dest;
	graphics->cur_blend_state.src_a = src;
	graphics->cur_blend_state.dest_a = dest;
	graphics->exports.device_blend_function(graphics->device, src, dest);
}