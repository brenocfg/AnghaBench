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
struct TYPE_4__ {scalar_t__ field; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct vpfe_video_device {scalar_t__ cur_frm; scalar_t__ next_frm; int /*<<< orphan*/  dma_queue_lock; int /*<<< orphan*/  dma_queue; TYPE_3__ fmt; int /*<<< orphan*/  started; } ;
struct vpfe_isif_device {struct vpfe_video_device video_out; } ;

/* Variables and functions */
 scalar_t__ V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_video_schedule_next_buffer (struct vpfe_video_device*) ; 

void vpfe_isif_vidint1_isr(struct vpfe_isif_device *isif)
{
	struct vpfe_video_device *video = &isif->video_out;

	if (!video->started)
		return;

	spin_lock(&video->dma_queue_lock);
	if (video->fmt.fmt.pix.field == V4L2_FIELD_NONE &&
	    !list_empty(&video->dma_queue) && video->cur_frm == video->next_frm)
		vpfe_video_schedule_next_buffer(video);

	spin_unlock(&video->dma_queue_lock);
}