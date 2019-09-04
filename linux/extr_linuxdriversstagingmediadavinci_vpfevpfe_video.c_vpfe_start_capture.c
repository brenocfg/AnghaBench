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
struct vpfe_pipeline {int /*<<< orphan*/  state; } ;
struct vpfe_video_device {int started; struct vpfe_pipeline pipe; } ;

/* Variables and functions */
 int vpfe_pipeline_set_stream (struct vpfe_pipeline*,int /*<<< orphan*/ ) ; 
 scalar_t__ vpfe_video_is_pipe_ready (struct vpfe_pipeline*) ; 

__attribute__((used)) static int vpfe_start_capture(struct vpfe_video_device *video)
{
	struct vpfe_pipeline *pipe = &video->pipe;
	int ret = 0;

	video->started = 1;
	if (vpfe_video_is_pipe_ready(pipe))
		ret = vpfe_pipeline_set_stream(pipe, pipe->state);

	return ret;
}