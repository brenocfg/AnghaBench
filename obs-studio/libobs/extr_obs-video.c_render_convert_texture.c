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
struct vec4 {int dummy; } ;
struct obs_core_video {int texture_converted; int /*<<< orphan*/ * conversion_techs; int /*<<< orphan*/ * convert_textures; int /*<<< orphan*/  conversion_width_i; int /*<<< orphan*/ * color_matrix; int /*<<< orphan*/ * conversion_effect; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gs_effect_set_float (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_effect_set_vec4 (int /*<<< orphan*/ *,struct vec4*) ; 
 int /*<<< orphan*/  gs_enable_blending (int) ; 
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_convert_plane (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_convert_texture_name ; 
 int /*<<< orphan*/  vec4_set (struct vec4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void render_convert_texture(struct obs_core_video *video,
				   gs_texture_t *texture)
{
	profile_start(render_convert_texture_name);

	gs_effect_t *effect = video->conversion_effect;
	gs_eparam_t *color_vec0 =
		gs_effect_get_param_by_name(effect, "color_vec0");
	gs_eparam_t *color_vec1 =
		gs_effect_get_param_by_name(effect, "color_vec1");
	gs_eparam_t *color_vec2 =
		gs_effect_get_param_by_name(effect, "color_vec2");
	gs_eparam_t *image = gs_effect_get_param_by_name(effect, "image");
	gs_eparam_t *width_i = gs_effect_get_param_by_name(effect, "width_i");

	struct vec4 vec0, vec1, vec2;
	vec4_set(&vec0, video->color_matrix[4], video->color_matrix[5],
		 video->color_matrix[6], video->color_matrix[7]);
	vec4_set(&vec1, video->color_matrix[0], video->color_matrix[1],
		 video->color_matrix[2], video->color_matrix[3]);
	vec4_set(&vec2, video->color_matrix[8], video->color_matrix[9],
		 video->color_matrix[10], video->color_matrix[11]);

	gs_enable_blending(false);

	if (video->convert_textures[0]) {
		gs_effect_set_texture(image, texture);
		gs_effect_set_vec4(color_vec0, &vec0);
		render_convert_plane(effect, video->convert_textures[0],
				     video->conversion_techs[0]);

		if (video->convert_textures[1]) {
			gs_effect_set_texture(image, texture);
			gs_effect_set_vec4(color_vec1, &vec1);
			if (!video->convert_textures[2])
				gs_effect_set_vec4(color_vec2, &vec2);
			gs_effect_set_float(width_i, video->conversion_width_i);
			render_convert_plane(effect, video->convert_textures[1],
					     video->conversion_techs[1]);

			if (video->convert_textures[2]) {
				gs_effect_set_texture(image, texture);
				gs_effect_set_vec4(color_vec2, &vec2);
				gs_effect_set_float(width_i,
						    video->conversion_width_i);
				render_convert_plane(
					effect, video->convert_textures[2],
					video->conversion_techs[2]);
			}
		}
	}

	gs_enable_blending(true);

	video->texture_converted = true;

	profile_end(render_convert_texture_name);
}