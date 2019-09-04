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
struct iss_device {int dummy; } ;
struct iss_csi2_device {int state; int output; int /*<<< orphan*/  subclk; int /*<<< orphan*/  phy; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; struct iss_video video_out; struct iss_device* iss; } ;

/* Variables and functions */
 int CSI2_OUTPUT_MEMORY ; 
 int ENODEV ; 
 int ETIMEDOUT ; 
#define  ISS_PIPELINE_STREAM_CONTINUOUS 129 
#define  ISS_PIPELINE_STREAM_STOPPED 128 
 int ISS_VIDEO_DMAQUEUE_QUEUED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csi2_configure (struct iss_csi2_device*) ; 
 int /*<<< orphan*/  csi2_ctx_enable (struct iss_csi2_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csi2_if_enable (struct iss_csi2_device*,int) ; 
 int /*<<< orphan*/  csi2_irq_ctx_set (struct iss_csi2_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csi2_print_status (struct iss_csi2_device*) ; 
 int /*<<< orphan*/  iss_video_dmaqueue_flags_clr (struct iss_video*) ; 
 int /*<<< orphan*/  omap4iss_csiphy_acquire (int /*<<< orphan*/ ) ; 
 int omap4iss_csiphy_config (struct iss_device*,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  omap4iss_csiphy_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4iss_module_sync_idle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap4iss_subclk_disable (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4iss_subclk_enable (struct iss_device*,int /*<<< orphan*/ ) ; 
 struct iss_csi2_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi2_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct iss_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	struct iss_device *iss = csi2->iss;
	struct iss_video *video_out = &csi2->video_out;
	int ret = 0;

	if (csi2->state == ISS_PIPELINE_STREAM_STOPPED) {
		if (enable == ISS_PIPELINE_STREAM_STOPPED)
			return 0;

		omap4iss_subclk_enable(iss, csi2->subclk);
	}

	switch (enable) {
	case ISS_PIPELINE_STREAM_CONTINUOUS: {
		ret = omap4iss_csiphy_config(iss, sd);
		if (ret < 0)
			return ret;

		if (omap4iss_csiphy_acquire(csi2->phy) < 0)
			return -ENODEV;
		csi2_configure(csi2);
		csi2_print_status(csi2);

		/*
		 * When outputting to memory with no buffer available, let the
		 * buffer queue handler start the hardware. A DMA queue flag
		 * ISS_VIDEO_DMAQUEUE_QUEUED will be set as soon as there is
		 * a buffer available.
		 */
		if (csi2->output & CSI2_OUTPUT_MEMORY &&
		    !(video_out->dmaqueue_flags & ISS_VIDEO_DMAQUEUE_QUEUED))
			break;
		/* Enable context 0 and IRQs */
		atomic_set(&csi2->stopping, 0);
		csi2_ctx_enable(csi2, 0, 1);
		csi2_if_enable(csi2, 1);
		iss_video_dmaqueue_flags_clr(video_out);
		break;
	}
	case ISS_PIPELINE_STREAM_STOPPED:
		if (csi2->state == ISS_PIPELINE_STREAM_STOPPED)
			return 0;
		if (omap4iss_module_sync_idle(&sd->entity, &csi2->wait,
					      &csi2->stopping))
			ret = -ETIMEDOUT;
		csi2_ctx_enable(csi2, 0, 0);
		csi2_if_enable(csi2, 0);
		csi2_irq_ctx_set(csi2, 0);
		omap4iss_csiphy_release(csi2->phy);
		omap4iss_subclk_disable(iss, csi2->subclk);
		iss_video_dmaqueue_flags_clr(video_out);
		break;
	}

	csi2->state = enable;
	return ret;
}