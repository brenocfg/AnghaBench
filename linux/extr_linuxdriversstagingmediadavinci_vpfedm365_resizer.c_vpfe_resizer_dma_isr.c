#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int field; } ;
struct TYPE_9__ {TYPE_3__ pix; } ;
struct TYPE_10__ {TYPE_4__ fmt; } ;
struct vpfe_pipeline {scalar_t__ state; int output_num; } ;
struct vpfe_video_device {scalar_t__ cur_frm; scalar_t__ next_frm; int field_id; int /*<<< orphan*/  dma_queue_lock; int /*<<< orphan*/  dma_queue; TYPE_5__ fmt; int /*<<< orphan*/  started; struct vpfe_pipeline pipe; } ;
struct TYPE_7__ {struct vpfe_video_device video_out; } ;
struct TYPE_6__ {struct vpfe_video_device video_out; } ;
struct vpfe_resizer_device {TYPE_2__ resizer_a; TYPE_1__ resizer_b; } ;
struct vpfe_device {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int V4L2_FIELD_NONE ; 
 scalar_t__ VPFE_PIPELINE_STREAM_SINGLESHOT ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resizer_ss_isr (struct vpfe_resizer_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_resizer_device*) ; 
 int vpfe_isif_get_fid (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_video_schedule_next_buffer (struct vpfe_video_device*) ; 

void vpfe_resizer_dma_isr(struct vpfe_resizer_device *resizer)
{
	struct vpfe_video_device *video_out2 = &resizer->resizer_b.video_out;
	struct vpfe_video_device *video_out = &resizer->resizer_a.video_out;
	struct vpfe_device *vpfe_dev = to_vpfe_device(resizer);
	struct vpfe_pipeline *pipe = &video_out->pipe;
	int schedule_capture = 0;
	enum v4l2_field field;
	int fid;

	if (!video_out->started)
		return;

	if (pipe->state == VPFE_PIPELINE_STREAM_SINGLESHOT) {
		resizer_ss_isr(resizer);
		return;
	}

	field = video_out->fmt.fmt.pix.field;
	if (field == V4L2_FIELD_NONE) {
		if (!list_empty(&video_out->dma_queue) &&
			video_out->cur_frm == video_out->next_frm)
			schedule_capture = 1;
	} else {
		fid = vpfe_isif_get_fid(vpfe_dev);
		if (fid == video_out->field_id) {
			/* we are in-sync here,continue */
			if (fid == 1 && !list_empty(&video_out->dma_queue) &&
			    video_out->cur_frm == video_out->next_frm)
				schedule_capture = 1;
		}
	}

	if (!schedule_capture)
		return;

	spin_lock(&video_out->dma_queue_lock);
	vpfe_video_schedule_next_buffer(video_out);
	spin_unlock(&video_out->dma_queue_lock);
	if (pipe->output_num > 1) {
		spin_lock(&video_out2->dma_queue_lock);
		vpfe_video_schedule_next_buffer(video_out2);
		spin_unlock(&video_out2->dma_queue_lock);
	}
}