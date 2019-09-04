#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vpfe_pipeline {int input_num; int output_num; TYPE_1__** outputs; TYPE_2__** inputs; } ;
struct vpfe_video_device {struct vpfe_pipeline pipe; } ;
struct TYPE_4__ {scalar_t__ started; } ;
struct TYPE_3__ {scalar_t__ started; } ;

/* Variables and functions */

__attribute__((used)) static int all_videos_stopped(struct vpfe_video_device *video)
{
	struct vpfe_pipeline *pipe = &video->pipe;
	int i;

	for (i = 0; i < pipe->input_num; i++)
		if (pipe->inputs[i]->started)
			return 0;
	for (i = 0; i < pipe->output_num; i++)
		if (pipe->outputs[i]->started)
			return 0;
	return 1;
}