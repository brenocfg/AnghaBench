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
struct vpfe_pipeline {int dummy; } ;
struct vpfe_video_device {scalar_t__ type; scalar_t__ started; struct vpfe_pipeline pipe; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  VPFE_PIPELINE_STREAM_STOPPED ; 
 scalar_t__ all_videos_stopped (struct vpfe_video_device*) ; 
 int /*<<< orphan*/  vpfe_pipeline_set_stream (struct vpfe_pipeline*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vpfe_stop_capture(struct vpfe_video_device *video)
{
	struct vpfe_pipeline *pipe = &video->pipe;

	video->started = 0;

	if (video->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return;
	if (all_videos_stopped(video))
		vpfe_pipeline_set_stream(pipe,
					 VPFE_PIPELINE_STREAM_STOPPED);
}