#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct obs_core_video {int /*<<< orphan*/ * graphics; int /*<<< orphan*/ * default_effect; int /*<<< orphan*/ * bilinear_lowres_effect; int /*<<< orphan*/ * area_effect; int /*<<< orphan*/ * lanczos_effect; int /*<<< orphan*/ * repeat_effect; int /*<<< orphan*/ * bicubic_effect; int /*<<< orphan*/ * conversion_effect; int /*<<< orphan*/ * solid_effect; int /*<<< orphan*/ * opaque_effect; int /*<<< orphan*/ * default_rect_effect; int /*<<< orphan*/  point_sampler; int /*<<< orphan*/  transparent_texture; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 int /*<<< orphan*/  gs_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_enter_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_leave_context () ; 
 int /*<<< orphan*/  gs_samplerstate_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ ) ; 
 TYPE_1__* obs ; 

__attribute__((used)) static void obs_free_graphics(void)
{
	struct obs_core_video *video = &obs->video;

	if (video->graphics) {
		gs_enter_context(video->graphics);

		gs_texture_destroy(video->transparent_texture);

		gs_samplerstate_destroy(video->point_sampler);

		gs_effect_destroy(video->default_effect);
		gs_effect_destroy(video->default_rect_effect);
		gs_effect_destroy(video->opaque_effect);
		gs_effect_destroy(video->solid_effect);
		gs_effect_destroy(video->conversion_effect);
		gs_effect_destroy(video->bicubic_effect);
		gs_effect_destroy(video->repeat_effect);
		gs_effect_destroy(video->lanczos_effect);
		gs_effect_destroy(video->area_effect);
		gs_effect_destroy(video->bilinear_lowres_effect);
		video->default_effect = NULL;

		gs_leave_context();

		gs_destroy(video->graphics);
		video->graphics = NULL;
	}
}