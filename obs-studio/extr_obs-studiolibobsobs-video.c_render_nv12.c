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
typedef  int /*<<< orphan*/  uint32_t ;
struct obs_core_video {int /*<<< orphan*/ * conversion_effect; int /*<<< orphan*/ ** output_textures; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_technique_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * gs_effect_get_technique (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_enable_blending (int) ; 
 int /*<<< orphan*/  gs_set_render_target (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t gs_technique_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_begin_pass (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  gs_technique_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_end_pass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_render_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void render_nv12(struct obs_core_video *video, gs_texture_t *target,
		int cur_texture, int prev_texture, const char *tech_name,
		uint32_t width, uint32_t height)
{
	gs_texture_t *texture = video->output_textures[prev_texture];

	gs_effect_t    *effect  = video->conversion_effect;
	gs_eparam_t    *image   = gs_effect_get_param_by_name(effect, "image");
	gs_technique_t *tech    = gs_effect_get_technique(effect, tech_name);
	size_t         passes, i;

	gs_effect_set_texture(image, texture);

	gs_set_render_target(target, NULL);
	set_render_size(width, height);

	gs_enable_blending(false);
	passes = gs_technique_begin(tech);
	for (i = 0; i < passes; i++) {
		gs_technique_begin_pass(tech, i);
		gs_draw_sprite(texture, 0, width, height);
		gs_technique_end_pass(tech);
	}
	gs_technique_end(tech);
	gs_enable_blending(true);

	UNUSED_PARAMETER(cur_texture);
}