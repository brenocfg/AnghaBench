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
struct video_output_info {int dummy; } ;
struct video_frame {int dummy; } ;
struct video_data {int /*<<< orphan*/  timestamp; } ;
struct obs_core_video {int /*<<< orphan*/  video; scalar_t__ gpu_conversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_rgbx_frame (struct video_frame*,struct video_data*,struct video_output_info const*) ; 
 int /*<<< orphan*/  set_gpu_converted_data (struct obs_core_video*,struct video_frame*,struct video_data*,struct video_output_info const*) ; 
 struct video_output_info* video_output_get_info (int /*<<< orphan*/ ) ; 
 int video_output_lock_frame (int /*<<< orphan*/ ,struct video_frame*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_output_unlock_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void output_video_data(struct obs_core_video *video,
				     struct video_data *input_frame, int count)
{
	const struct video_output_info *info;
	struct video_frame output_frame;
	bool locked;

	info = video_output_get_info(video->video);

	locked = video_output_lock_frame(video->video, &output_frame, count,
					 input_frame->timestamp);
	if (locked) {
		if (video->gpu_conversion) {
			set_gpu_converted_data(video, &output_frame,
					       input_frame, info);
		} else {
			copy_rgbx_frame(&output_frame, input_frame, info);
		}

		video_output_unlock_frame(video->video);
	}
}