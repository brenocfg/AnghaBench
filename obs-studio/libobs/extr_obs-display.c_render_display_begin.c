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
typedef  scalar_t__ uint32_t ;
struct vec4 {float w; } ;
struct obs_display {int /*<<< orphan*/  background_color; int /*<<< orphan*/  swap; } ;

/* Variables and functions */
 int GS_CLEAR_COLOR ; 
 int GS_CLEAR_DEPTH ; 
 int GS_CLEAR_STENCIL ; 
 int /*<<< orphan*/  GS_NEITHER ; 
 int /*<<< orphan*/  gs_begin_scene () ; 
 int /*<<< orphan*/  gs_clear (int,struct vec4*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_enable_depth_test (int) ; 
 int /*<<< orphan*/  gs_load_swapchain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_ortho (float,float,float,float,float,float) ; 
 int /*<<< orphan*/  gs_resize (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gs_set_cull_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_set_viewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vec4_from_rgba (struct vec4*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void render_display_begin(struct obs_display *display,
					uint32_t cx, uint32_t cy,
					bool size_changed)
{
	struct vec4 clear_color;

	gs_load_swapchain(display->swap);

	if (size_changed)
		gs_resize(cx, cy);

	gs_begin_scene();

	vec4_from_rgba(&clear_color, display->background_color);
	clear_color.w = 1.0f;

	gs_clear(GS_CLEAR_COLOR | GS_CLEAR_DEPTH | GS_CLEAR_STENCIL,
		 &clear_color, 1.0f, 0);

	gs_enable_depth_test(false);
	/* gs_enable_blending(false); */
	gs_set_cull_mode(GS_NEITHER);

	gs_ortho(0.0f, (float)cx, 0.0f, (float)cy, -100.0f, 100.0f);
	gs_set_viewport(0, 0, cx, cy);
}