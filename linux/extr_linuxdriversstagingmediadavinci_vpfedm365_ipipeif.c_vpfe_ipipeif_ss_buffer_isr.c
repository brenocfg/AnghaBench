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
struct vpfe_video_device {int /*<<< orphan*/  dma_queue_lock; int /*<<< orphan*/  state; } ;
struct vpfe_ipipeif_device {scalar_t__ input; struct vpfe_video_device video_in; } ;

/* Variables and functions */
 scalar_t__ IPIPEIF_INPUT_MEMORY ; 
 int /*<<< orphan*/  VPFE_VIDEO_BUFFER_NOT_QUEUED ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_video_process_buffer_complete (struct vpfe_video_device*) ; 
 int /*<<< orphan*/  vpfe_video_schedule_next_buffer (struct vpfe_video_device*) ; 

void vpfe_ipipeif_ss_buffer_isr(struct vpfe_ipipeif_device *ipipeif)
{
	struct vpfe_video_device *video_in = &ipipeif->video_in;

	if (ipipeif->input != IPIPEIF_INPUT_MEMORY)
		return;

	spin_lock(&video_in->dma_queue_lock);
	vpfe_video_process_buffer_complete(video_in);
	video_in->state = VPFE_VIDEO_BUFFER_NOT_QUEUED;
	vpfe_video_schedule_next_buffer(video_in);
	spin_unlock(&video_in->dma_queue_lock);
}