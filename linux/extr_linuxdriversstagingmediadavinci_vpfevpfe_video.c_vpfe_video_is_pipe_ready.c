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
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  started; } ;
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  started; } ;

/* Variables and functions */
 scalar_t__ VPFE_VIDEO_BUFFER_QUEUED ; 

int vpfe_video_is_pipe_ready(struct vpfe_pipeline *pipe)
{
	int i;

	for (i = 0; i < pipe->input_num; i++)
		if (!pipe->inputs[i]->started ||
			pipe->inputs[i]->state != VPFE_VIDEO_BUFFER_QUEUED)
			return 0;
	for (i = 0; i < pipe->output_num; i++)
		if (!pipe->outputs[i]->started ||
			pipe->outputs[i]->state != VPFE_VIDEO_BUFFER_QUEUED)
			return 0;
	return 1;
}