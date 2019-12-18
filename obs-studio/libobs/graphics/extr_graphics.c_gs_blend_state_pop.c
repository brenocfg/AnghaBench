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
struct blend_state {int /*<<< orphan*/  dest_a; int /*<<< orphan*/  src_a; int /*<<< orphan*/  dest_c; int /*<<< orphan*/  src_c; int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/  blend_state_stack; } ;
typedef  TYPE_1__ graphics_t ;

/* Variables and functions */
 struct blend_state* da_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_pop_back (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_blend_function_separate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_enable_blending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_valid (char*) ; 
 TYPE_1__* thread_graphics ; 

void gs_blend_state_pop(void)
{
	graphics_t *graphics = thread_graphics;
	struct blend_state *state;

	if (!gs_valid("gs_blend_state_pop"))
		return;

	state = da_end(graphics->blend_state_stack);
	if (!state)
		return;

	gs_enable_blending(state->enabled);
	gs_blend_function_separate(state->src_c, state->dest_c, state->src_a,
				   state->dest_a);

	da_pop_back(graphics->blend_state_stack);
}