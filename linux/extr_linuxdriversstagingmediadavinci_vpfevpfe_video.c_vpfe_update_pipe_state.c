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
struct vpfe_pipeline {scalar_t__ input_num; int /*<<< orphan*/  state; } ;
struct vpfe_video_device {int initialized; int skip_frame_count; int skip_frame_count_init; struct vpfe_pipeline pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPFE_PIPELINE_STREAM_CONTINUOUS ; 
 int /*<<< orphan*/  VPFE_PIPELINE_STREAM_SINGLESHOT ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int vpfe_prepare_pipeline (struct vpfe_video_device*) ; 
 int vpfe_update_current_ext_subdev (struct vpfe_video_device*) ; 

__attribute__((used)) static int vpfe_update_pipe_state(struct vpfe_video_device *video)
{
	struct vpfe_pipeline *pipe = &video->pipe;
	int ret;

	ret = vpfe_prepare_pipeline(video);
	if (ret)
		return ret;

	/*
	 * Find out if there is any input video
	 * if yes, it is single shot.
	 */
	if (pipe->input_num == 0) {
		pipe->state = VPFE_PIPELINE_STREAM_CONTINUOUS;
		ret = vpfe_update_current_ext_subdev(video);
		if (ret) {
			pr_err("Invalid external subdev\n");
			return ret;
		}
	} else {
		pipe->state = VPFE_PIPELINE_STREAM_SINGLESHOT;
	}
	video->initialized = 1;
	video->skip_frame_count = 1;
	video->skip_frame_count_init = 1;
	return 0;
}