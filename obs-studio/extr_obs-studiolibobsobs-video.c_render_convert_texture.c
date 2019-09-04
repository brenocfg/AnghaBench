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
struct obs_core_video {int* textures_converted; scalar_t__ conversion_height; scalar_t__ output_width; scalar_t__* plane_offsets; int /*<<< orphan*/ * textures_output; int /*<<< orphan*/  conversion_tech; int /*<<< orphan*/ * conversion_effect; scalar_t__ output_height; int /*<<< orphan*/ ** convert_textures; int /*<<< orphan*/ ** output_textures; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_technique_t ;
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_draw_sprite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * gs_effect_get_technique (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_effect_set_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_enable_blending (int) ; 
 int /*<<< orphan*/  gs_set_render_target (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t gs_technique_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_begin_pass (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  gs_technique_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_end_pass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_convert_texture_name ; 
 int /*<<< orphan*/  set_eparam (int /*<<< orphan*/ *,char*,float) ; 
 int /*<<< orphan*/  set_render_size (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void render_convert_texture(struct obs_core_video *video,
		int cur_texture, int prev_texture)
{
	profile_start(render_convert_texture_name);

	gs_texture_t *texture = video->output_textures[prev_texture];
	gs_texture_t *target  = video->convert_textures[cur_texture];
	float        fwidth  = (float)video->output_width;
	float        fheight = (float)video->output_height;
	size_t       passes, i;

	gs_effect_t    *effect  = video->conversion_effect;
	gs_eparam_t    *image   = gs_effect_get_param_by_name(effect, "image");
	gs_technique_t *tech    = gs_effect_get_technique(effect,
			video->conversion_tech);

	if (!video->textures_output[prev_texture])
		goto end;

	set_eparam(effect, "u_plane_offset", (float)video->plane_offsets[1]);
	set_eparam(effect, "v_plane_offset", (float)video->plane_offsets[2]);
	set_eparam(effect, "width",  fwidth);
	set_eparam(effect, "height", fheight);
	set_eparam(effect, "width_i",  1.0f / fwidth);
	set_eparam(effect, "height_i", 1.0f / fheight);
	set_eparam(effect, "width_d2",  fwidth  * 0.5f);
	set_eparam(effect, "height_d2", fheight * 0.5f);
	set_eparam(effect, "width_d2_i",  1.0f / (fwidth  * 0.5f));
	set_eparam(effect, "height_d2_i", 1.0f / (fheight * 0.5f));
	set_eparam(effect, "input_height", (float)video->conversion_height);

	gs_effect_set_texture(image, texture);

	gs_set_render_target(target, NULL);
	set_render_size(video->output_width, video->conversion_height);

	gs_enable_blending(false);
	passes = gs_technique_begin(tech);
	for (i = 0; i < passes; i++) {
		gs_technique_begin_pass(tech, i);
		gs_draw_sprite(texture, 0, video->output_width,
				video->conversion_height);
		gs_technique_end_pass(tech);
	}
	gs_technique_end(tech);
	gs_enable_blending(true);

	video->textures_converted[cur_texture] = true;

end:
	profile_end(render_convert_texture_name);
}