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
struct TYPE_4__ {int field; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct vpfe_video_device {scalar_t__ cur_frm; scalar_t__ next_frm; int field_id; int /*<<< orphan*/  dma_queue_lock; int /*<<< orphan*/  dma_queue; TYPE_3__ fmt; int /*<<< orphan*/  started; } ;
struct vpfe_isif_device {struct vpfe_video_device video_out; } ;
struct vpfe_device {int dummy; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 int V4L2_FIELD_NONE ; 
 int V4L2_FIELD_SEQ_TB ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_isif_device*) ; 
 int vpfe_isif_get_fid (struct vpfe_device*) ; 
 int /*<<< orphan*/  vpfe_video_process_buffer_complete (struct vpfe_video_device*) ; 
 int /*<<< orphan*/  vpfe_video_schedule_bottom_field (struct vpfe_video_device*) ; 
 int /*<<< orphan*/  vpfe_video_schedule_next_buffer (struct vpfe_video_device*) ; 

void vpfe_isif_buffer_isr(struct vpfe_isif_device *isif)
{
	struct vpfe_device *vpfe_dev = to_vpfe_device(isif);
	struct vpfe_video_device *video = &isif->video_out;
	enum v4l2_field field;
	int fid;

	if (!video->started)
		return;

	field = video->fmt.fmt.pix.field;

	if (field == V4L2_FIELD_NONE) {
		/* handle progressive frame capture */
		if (video->cur_frm != video->next_frm)
			vpfe_video_process_buffer_complete(video);
		return;
	}

	/* interlaced or TB capture check which field we
	 * are in hardware
	 */
	fid = vpfe_isif_get_fid(vpfe_dev);

	/* switch the software maintained field id */
	video->field_id ^= 1;
	if (fid == video->field_id) {
		/* we are in-sync here,continue */
		if (fid == 0) {
			/*
			 * One frame is just being captured. If the
			 * next frame is available, release the current
			 * frame and move on
			 */
			if (video->cur_frm != video->next_frm)
				vpfe_video_process_buffer_complete(video);
			/*
			 * based on whether the two fields are stored
			 * interleavely or separately in memory,
			 * reconfigure the ISIF memory address
			 */
			if (field == V4L2_FIELD_SEQ_TB)
				vpfe_video_schedule_bottom_field(video);
			return;
		}
		/*
		 * if one field is just being captured configure
		 * the next frame get the next frame from the
		 * empty queue if no frame is available hold on
		 * to the current buffer
		 */
		spin_lock(&video->dma_queue_lock);
		if (!list_empty(&video->dma_queue) &&
		video->cur_frm == video->next_frm)
			vpfe_video_schedule_next_buffer(video);
		spin_unlock(&video->dma_queue_lock);
	} else if (fid == 0) {
		/*
		 * out of sync. Recover from any hardware out-of-sync.
		 * May loose one frame
		 */
		video->field_id = fid;
	}
}