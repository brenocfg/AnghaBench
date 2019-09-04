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
struct obs_core_video {int output_width; int output_height; int* textures_converted; int /*<<< orphan*/ * convert_uv_textures; int /*<<< orphan*/ * convert_textures; int /*<<< orphan*/ * textures_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_convert_nv12_name ; 
 int /*<<< orphan*/  render_nv12 (struct obs_core_video*,int /*<<< orphan*/ ,int,int,char*,int,int) ; 

__attribute__((used)) static void render_convert_texture_nv12(struct obs_core_video *video,
		int cur_texture, int prev_texture)
{
	profile_start(render_convert_nv12_name);

	if (!video->textures_output[prev_texture])
		goto end;

	render_nv12(video, video->convert_textures[cur_texture],
			cur_texture, prev_texture, "NV12_Y",
			video->output_width, video->output_height);
	render_nv12(video, video->convert_uv_textures[cur_texture],
			cur_texture, prev_texture, "NV12_UV",
			video->output_width / 2, video->output_height / 2);

	video->textures_converted[cur_texture] = true;

end:
	profile_end(render_convert_nv12_name);
}