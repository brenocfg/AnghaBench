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
typedef  int /*<<< orphan*/  vframe_info ;
struct video_data {int /*<<< orphan*/  timestamp; } ;
struct obs_vframe_info {int /*<<< orphan*/  count; int /*<<< orphan*/  timestamp; } ;
struct obs_core_video {int cur_texture; int /*<<< orphan*/  vframe_info_buffer; int /*<<< orphan*/  graphics; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_DEBUG_COLOR_RENDER_VIDEO ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_BEGIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GS_DEBUG_MARKER_END () ; 
 int NUM_TEXTURES ; 
 int /*<<< orphan*/  circlebuf_pop_front (int /*<<< orphan*/ *,struct obs_vframe_info*,int) ; 
 int download_frame (struct obs_core_video*,int,struct video_data*) ; 
 int /*<<< orphan*/  gs_enter_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_flush () ; 
 int /*<<< orphan*/  gs_leave_context () ; 
 int /*<<< orphan*/  memset (struct video_data*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* obs ; 
 int /*<<< orphan*/  output_frame_download_frame_name ; 
 int /*<<< orphan*/  output_frame_gs_context_name ; 
 int /*<<< orphan*/  output_frame_gs_flush_name ; 
 int /*<<< orphan*/  output_frame_output_video_data_name ; 
 int /*<<< orphan*/  output_frame_render_video_name ; 
 int /*<<< orphan*/  output_video_data (struct obs_core_video*,struct video_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  profile_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_video (struct obs_core_video*,int,int const,int) ; 

__attribute__((used)) static inline void output_frame(bool raw_active, const bool gpu_active)
{
	struct obs_core_video *video = &obs->video;
	int cur_texture = video->cur_texture;
	int prev_texture = cur_texture == 0 ? NUM_TEXTURES - 1
					    : cur_texture - 1;
	struct video_data frame;
	bool frame_ready = 0;

	memset(&frame, 0, sizeof(struct video_data));

	profile_start(output_frame_gs_context_name);
	gs_enter_context(video->graphics);

	profile_start(output_frame_render_video_name);
	GS_DEBUG_MARKER_BEGIN(GS_DEBUG_COLOR_RENDER_VIDEO,
			      output_frame_render_video_name);
	render_video(video, raw_active, gpu_active, cur_texture);
	GS_DEBUG_MARKER_END();
	profile_end(output_frame_render_video_name);

	if (raw_active) {
		profile_start(output_frame_download_frame_name);
		frame_ready = download_frame(video, prev_texture, &frame);
		profile_end(output_frame_download_frame_name);
	}

	profile_start(output_frame_gs_flush_name);
	gs_flush();
	profile_end(output_frame_gs_flush_name);

	gs_leave_context();
	profile_end(output_frame_gs_context_name);

	if (raw_active && frame_ready) {
		struct obs_vframe_info vframe_info;
		circlebuf_pop_front(&video->vframe_info_buffer, &vframe_info,
				    sizeof(vframe_info));

		frame.timestamp = vframe_info.timestamp;
		profile_start(output_frame_output_video_data_name);
		output_video_data(video, &frame, vframe_info.count);
		profile_end(output_frame_output_video_data_name);
	}

	if (++video->cur_texture == NUM_TEXTURES)
		video->cur_texture = 0;
}