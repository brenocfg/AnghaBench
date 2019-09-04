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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct vpfe_pipeline {int output_num; } ;
struct vpfe_video_device {int /*<<< orphan*/  dma_queue_lock; void* state; struct vpfe_pipeline pipe; } ;
struct TYPE_6__ {scalar_t__ output; struct vpfe_video_device video_out; } ;
struct TYPE_5__ {scalar_t__ output; struct vpfe_video_device video_out; } ;
struct vpfe_resizer_device {TYPE_3__ resizer_a; TYPE_2__ resizer_b; } ;
struct TYPE_4__ {scalar_t__ input; } ;
struct vpfe_device {TYPE_1__ vpfe_ipipeif; } ;

/* Variables and functions */
 scalar_t__ IPIPEIF_INPUT_MEMORY ; 
 scalar_t__ RESIZER_OUTPUT_MEMORY ; 
 void* VPFE_VIDEO_BUFFER_NOT_QUEUED ; 
 int /*<<< orphan*/  resizer_enable (struct vpfe_resizer_device*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_resizer_device*) ; 
 int /*<<< orphan*/  vpfe_ipipe_enable (struct vpfe_device*,int) ; 
 int /*<<< orphan*/  vpfe_ipipeif_enable (struct vpfe_device*) ; 
 scalar_t__ vpfe_video_is_pipe_ready (struct vpfe_pipeline*) ; 
 int /*<<< orphan*/  vpfe_video_process_buffer_complete (struct vpfe_video_device*) ; 
 int /*<<< orphan*/  vpfe_video_schedule_next_buffer (struct vpfe_video_device*) ; 
 int vpss_dma_complete_interrupt () ; 

__attribute__((used)) static void resizer_ss_isr(struct vpfe_resizer_device *resizer)
{
	struct vpfe_video_device *video_out = &resizer->resizer_a.video_out;
	struct vpfe_video_device *video_out2 = &resizer->resizer_b.video_out;
	struct vpfe_device *vpfe_dev = to_vpfe_device(resizer);
	struct vpfe_pipeline *pipe = &video_out->pipe;
	u16 ipipeif_sink = vpfe_dev->vpfe_ipipeif.input;
	u32 val;

	if (ipipeif_sink != IPIPEIF_INPUT_MEMORY)
		return;

	if (resizer->resizer_a.output == RESIZER_OUTPUT_MEMORY) {
		val = vpss_dma_complete_interrupt();
		if (val != 0 && val != 2)
			return;
	}

	if (resizer->resizer_a.output == RESIZER_OUTPUT_MEMORY) {
		spin_lock(&video_out->dma_queue_lock);
		vpfe_video_process_buffer_complete(video_out);
		video_out->state = VPFE_VIDEO_BUFFER_NOT_QUEUED;
		vpfe_video_schedule_next_buffer(video_out);
		spin_unlock(&video_out->dma_queue_lock);
	}

	/* If resizer B is enabled */
	if (pipe->output_num > 1 && resizer->resizer_b.output ==
	    RESIZER_OUTPUT_MEMORY) {
		spin_lock(&video_out2->dma_queue_lock);
		vpfe_video_process_buffer_complete(video_out2);
		video_out2->state = VPFE_VIDEO_BUFFER_NOT_QUEUED;
		vpfe_video_schedule_next_buffer(video_out2);
		spin_unlock(&video_out2->dma_queue_lock);
	}

	/* start HW if buffers are queued */
	if (vpfe_video_is_pipe_ready(pipe) &&
	    resizer->resizer_a.output == RESIZER_OUTPUT_MEMORY) {
		resizer_enable(resizer, 1);
		vpfe_ipipe_enable(vpfe_dev, 1);
		vpfe_ipipeif_enable(vpfe_dev);
	}
}