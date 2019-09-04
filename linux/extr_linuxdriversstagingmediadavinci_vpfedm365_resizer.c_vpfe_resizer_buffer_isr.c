#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int field; } ;
struct TYPE_11__ {TYPE_4__ pix; } ;
struct TYPE_12__ {TYPE_5__ fmt; } ;
struct vpfe_pipeline {int output_num; } ;
struct vpfe_video_device {scalar_t__ cur_frm; scalar_t__ next_frm; int field_id; scalar_t__ skip_frame_count_init; scalar_t__ skip_frame_count; TYPE_6__ fmt; int /*<<< orphan*/  started; struct vpfe_pipeline pipe; } ;
struct TYPE_9__ {scalar_t__ input; } ;
struct TYPE_8__ {struct vpfe_video_device video_out; } ;
struct TYPE_7__ {struct vpfe_video_device video_out; } ;
struct vpfe_resizer_device {int /*<<< orphan*/  base_addr; TYPE_3__ crop_resizer; TYPE_2__ resizer_a; TYPE_1__ resizer_b; } ;
struct vpfe_device {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 scalar_t__ RESIZER_CROP_INPUT_NONE ; 
 int V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  rsz_src_enable (int /*<<< orphan*/ ,int) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_resizer_device*) ; 
 int vpfe_isif_get_fid (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_video_process_buffer_complete (struct vpfe_video_device*) ; 

void vpfe_resizer_buffer_isr(struct vpfe_resizer_device *resizer)
{
	struct vpfe_device *vpfe_dev = to_vpfe_device(resizer);
	struct vpfe_video_device *video_out = &resizer->resizer_a.video_out;
	struct vpfe_video_device *video_out2 = &resizer->resizer_b.video_out;
	struct vpfe_pipeline *pipe = &resizer->resizer_a.video_out.pipe;
	enum v4l2_field field;
	int fid;

	if (!video_out->started)
		return;

	if (resizer->crop_resizer.input == RESIZER_CROP_INPUT_NONE)
		return;

	field = video_out->fmt.fmt.pix.field;
	if (field == V4L2_FIELD_NONE) {
		/* handle progressive frame capture */
		if (video_out->cur_frm != video_out->next_frm) {
			vpfe_video_process_buffer_complete(video_out);
			if (pipe->output_num > 1)
				vpfe_video_process_buffer_complete(video_out2);
		}

		video_out->skip_frame_count--;
		if (!video_out->skip_frame_count) {
			video_out->skip_frame_count =
				video_out->skip_frame_count_init;
			rsz_src_enable(resizer->base_addr, 1);
		} else {
			rsz_src_enable(resizer->base_addr, 0);
		}
		return;
	}

	/* handle interlaced frame capture */
	fid = vpfe_isif_get_fid(vpfe_dev);

	/* switch the software maintained field id */
	video_out->field_id ^= 1;
	if (fid == video_out->field_id) {
		/*
		 * we are in-sync here,continue.
		 * One frame is just being captured. If the
		 * next frame is available, release the current
		 * frame and move on
		 */
		if (fid == 0 && video_out->cur_frm != video_out->next_frm) {
			vpfe_video_process_buffer_complete(video_out);
			if (pipe->output_num > 1)
				vpfe_video_process_buffer_complete(video_out2);
		}
	} else if (fid == 0) {
		/*
		 * out of sync. Recover from any hardware out-of-sync.
		 * May loose one frame
		 */
		video_out->field_id = fid;
	}
}