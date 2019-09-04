#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vpfe_pipeline {scalar_t__ state; } ;
struct vpfe_video_device {TYPE_2__* next_frm; TYPE_2__* cur_frm; struct vpfe_pipeline pipe; } ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_4__ {TYPE_3__ vb2_buf; } ;
struct TYPE_5__ {TYPE_1__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 scalar_t__ VPFE_PIPELINE_STREAM_CONTINUOUS ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 

void vpfe_video_process_buffer_complete(struct vpfe_video_device *video)
{
	struct vpfe_pipeline *pipe = &video->pipe;

	video->cur_frm->vb.vb2_buf.timestamp = ktime_get_ns();
	vb2_buffer_done(&video->cur_frm->vb.vb2_buf, VB2_BUF_STATE_DONE);
	if (pipe->state == VPFE_PIPELINE_STREAM_CONTINUOUS)
		video->cur_frm = video->next_frm;
}