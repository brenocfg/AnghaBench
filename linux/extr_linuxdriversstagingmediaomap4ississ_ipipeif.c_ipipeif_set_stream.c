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
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct iss_video {int dmaqueue_flags; } ;
struct iss_ipipeif_device {int state; int output; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; struct iss_video video_out; } ;
struct iss_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IPIPEIF_DRV_SUBCLK_MASK ; 
 int IPIPEIF_OUTPUT_MEMORY ; 
#define  ISS_PIPELINE_STREAM_CONTINUOUS 129 
#define  ISS_PIPELINE_STREAM_STOPPED 128 
 int ISS_VIDEO_DMAQUEUE_QUEUED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipipeif_configure (struct iss_ipipeif_device*) ; 
 int /*<<< orphan*/  ipipeif_enable (struct iss_ipipeif_device*,int) ; 
 int /*<<< orphan*/  ipipeif_print_status (struct iss_ipipeif_device*) ; 
 int /*<<< orphan*/  ipipeif_write_enable (struct iss_ipipeif_device*,int) ; 
 int /*<<< orphan*/  iss_video_dmaqueue_flags_clr (struct iss_video*) ; 
 int /*<<< orphan*/  omap4iss_isp_subclk_disable (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4iss_isp_subclk_enable (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4iss_module_sync_idle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct iss_device* to_iss_device (struct iss_ipipeif_device*) ; 
 struct iss_ipipeif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ipipeif_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct iss_ipipeif_device *ipipeif = v4l2_get_subdevdata(sd);
	struct iss_device *iss = to_iss_device(ipipeif);
	struct iss_video *video_out = &ipipeif->video_out;
	int ret = 0;

	if (ipipeif->state == ISS_PIPELINE_STREAM_STOPPED) {
		if (enable == ISS_PIPELINE_STREAM_STOPPED)
			return 0;

		omap4iss_isp_subclk_enable(iss, IPIPEIF_DRV_SUBCLK_MASK);
	}

	switch (enable) {
	case ISS_PIPELINE_STREAM_CONTINUOUS:

		ipipeif_configure(ipipeif);
		ipipeif_print_status(ipipeif);

		/*
		 * When outputting to memory with no buffer available, let the
		 * buffer queue handler start the hardware. A DMA queue flag
		 * ISS_VIDEO_DMAQUEUE_QUEUED will be set as soon as there is
		 * a buffer available.
		 */
		if (ipipeif->output & IPIPEIF_OUTPUT_MEMORY &&
		    !(video_out->dmaqueue_flags & ISS_VIDEO_DMAQUEUE_QUEUED))
			break;

		atomic_set(&ipipeif->stopping, 0);
		if (ipipeif->output & IPIPEIF_OUTPUT_MEMORY)
			ipipeif_write_enable(ipipeif, 1);
		ipipeif_enable(ipipeif, 1);
		iss_video_dmaqueue_flags_clr(video_out);
		break;

	case ISS_PIPELINE_STREAM_STOPPED:
		if (ipipeif->state == ISS_PIPELINE_STREAM_STOPPED)
			return 0;
		if (omap4iss_module_sync_idle(&sd->entity, &ipipeif->wait,
					      &ipipeif->stopping))
			ret = -ETIMEDOUT;

		if (ipipeif->output & IPIPEIF_OUTPUT_MEMORY)
			ipipeif_write_enable(ipipeif, 0);
		ipipeif_enable(ipipeif, 0);
		omap4iss_isp_subclk_disable(iss, IPIPEIF_DRV_SUBCLK_MASK);
		iss_video_dmaqueue_flags_clr(video_out);
		break;
	}

	ipipeif->state = enable;
	return ret;
}