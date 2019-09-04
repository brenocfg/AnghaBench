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
struct obs_core_video {scalar_t__ cur_texture; scalar_t__ gpu_encoder_active; int /*<<< orphan*/  gpu_encoders; int /*<<< orphan*/  gpu_encoder_mutex; int /*<<< orphan*/  textures_converted; int /*<<< orphan*/  textures_copied; int /*<<< orphan*/  textures_output; int /*<<< orphan*/  textures_rendered; int /*<<< orphan*/  vframe_info_buffer_gpu; int /*<<< orphan*/  vframe_info_buffer; int /*<<< orphan*/ ** output_textures; int /*<<< orphan*/ ** convert_uv_textures; int /*<<< orphan*/ ** convert_textures; int /*<<< orphan*/ ** render_textures; int /*<<< orphan*/ ** copy_surfaces; int /*<<< orphan*/ * mapped_surface; int /*<<< orphan*/  graphics; int /*<<< orphan*/ * video; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 size_t NUM_TEXTURES ; 
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_enter_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_leave_context () ; 
 int /*<<< orphan*/  gs_stagesurface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_stagesurface_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_texture_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_output_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void obs_free_video(void)
{
	struct obs_core_video *video = &obs->video;

	if (video->video) {
		video_output_close(video->video);
		video->video = NULL;

		if (!video->graphics)
			return;

		gs_enter_context(video->graphics);

		if (video->mapped_surface) {
			gs_stagesurface_unmap(video->mapped_surface);
			video->mapped_surface = NULL;
		}

		for (size_t i = 0; i < NUM_TEXTURES; i++) {
			gs_stagesurface_destroy(video->copy_surfaces[i]);
			gs_texture_destroy(video->render_textures[i]);
			gs_texture_destroy(video->convert_textures[i]);
			gs_texture_destroy(video->convert_uv_textures[i]);
			gs_texture_destroy(video->output_textures[i]);

			video->copy_surfaces[i]       = NULL;
			video->render_textures[i]     = NULL;
			video->convert_textures[i]    = NULL;
			video->convert_uv_textures[i] = NULL;
			video->output_textures[i]     = NULL;
		}

		gs_leave_context();

		circlebuf_free(&video->vframe_info_buffer);
		circlebuf_free(&video->vframe_info_buffer_gpu);

		memset(&video->textures_rendered, 0,
				sizeof(video->textures_rendered));
		memset(&video->textures_output, 0,
				sizeof(video->textures_output));
		memset(&video->textures_copied, 0,
				sizeof(video->textures_copied));
		memset(&video->textures_converted, 0,
				sizeof(video->textures_converted));

		pthread_mutex_destroy(&video->gpu_encoder_mutex);
		pthread_mutex_init_value(&video->gpu_encoder_mutex);
		da_free(video->gpu_encoders);

		video->gpu_encoder_active = 0;
		video->cur_texture = 0;
	}
}