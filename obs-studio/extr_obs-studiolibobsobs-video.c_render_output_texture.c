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
typedef  int /*<<< orphan*/  uint32_t ;
struct vec2 {int dummy; } ;
struct TYPE_2__ {scalar_t__ output_format; } ;
struct obs_core_video {int* textures_output; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/ * textures_rendered; TYPE_1__ ovi; scalar_t__ base_height; scalar_t__ base_width; int /*<<< orphan*/ ** output_textures; int /*<<< orphan*/ ** render_textures; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_technique_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 scalar_t__ VIDEO_FORMAT_RGBA ; 
 int /*<<< orphan*/ * get_scale_effect (struct obs_core_video*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * gs_effect_get_technique (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_set_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gs_effect_set_vec2 (int /*<<< orphan*/ *,struct vec2*) ; 
 int /*<<< orphan*/  gs_enable_blending (int) ; 
 int /*<<< orphan*/  gs_set_render_target (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t gs_technique_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_begin_pass (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  gs_technique_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_end_pass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_texture_get_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_texture_get_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_output_texture_name ; 
 int /*<<< orphan*/  set_render_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec2_set (struct vec2*,float,float) ; 

__attribute__((used)) static inline void render_output_texture(struct obs_core_video *video,
		int cur_texture, int prev_texture)
{
	profile_start(render_output_texture_name);

	gs_texture_t *texture = video->render_textures[prev_texture];
	gs_texture_t *target  = video->output_textures[cur_texture];
	uint32_t     width   = gs_texture_get_width(target);
	uint32_t     height  = gs_texture_get_height(target);
	struct vec2  base_i;

	vec2_set(&base_i,
		1.0f / (float)video->base_width,
		1.0f / (float)video->base_height);

	gs_effect_t    *effect  = get_scale_effect(video, width, height);
	gs_technique_t *tech;

	if (video->ovi.output_format == VIDEO_FORMAT_RGBA) {
		tech = gs_effect_get_technique(effect, "Draw");
	} else {
		tech = gs_effect_get_technique(effect, "DrawMatrix");
	}

	gs_eparam_t    *image   = gs_effect_get_param_by_name(effect, "image");
	gs_eparam_t    *matrix  = gs_effect_get_param_by_name(effect,
			"color_matrix");
	gs_eparam_t    *bres_i  = gs_effect_get_param_by_name(effect,
			"base_dimension_i");
	size_t      passes, i;

	if (!video->textures_rendered[prev_texture])
		goto end;

	gs_set_render_target(target, NULL);
	set_render_size(width, height);

	if (bres_i)
		gs_effect_set_vec2(bres_i, &base_i);

	gs_effect_set_val(matrix, video->color_matrix, sizeof(float) * 16);
	gs_effect_set_texture(image, texture);

	gs_enable_blending(false);
	passes = gs_technique_begin(tech);
	for (i = 0; i < passes; i++) {
		gs_technique_begin_pass(tech, i);
		gs_draw_sprite(texture, 0, width, height);
		gs_technique_end_pass(tech);
	}
	gs_technique_end(tech);
	gs_enable_blending(true);

	video->textures_output[cur_texture] = true;

end:
	profile_end(render_output_texture_name);
}