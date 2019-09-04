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
struct iss_resizer_device {int state; int output; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; struct iss_video video_out; } ;
struct iss_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
#define  ISS_PIPELINE_STREAM_CONTINUOUS 129 
#define  ISS_PIPELINE_STREAM_STOPPED 128 
 int ISS_VIDEO_DMAQUEUE_QUEUED ; 
 int /*<<< orphan*/  OMAP4_ISS_ISP_SUBCLK_RSZ ; 
 int /*<<< orphan*/  OMAP4_ISS_MEM_ISP_RESIZER ; 
 int RESIZER_OUTPUT_MEMORY ; 
 int /*<<< orphan*/  RSZ_GCK_MMR ; 
 int /*<<< orphan*/  RSZ_GCK_MMR_MMR ; 
 int /*<<< orphan*/  RSZ_GCK_SDR ; 
 int /*<<< orphan*/  RSZ_GCK_SDR_CORE ; 
 int /*<<< orphan*/  RSZ_SYSCONFIG ; 
 int /*<<< orphan*/  RSZ_SYSCONFIG_RSZA_CLK_EN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_clr (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_reg_set (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iss_video_dmaqueue_flags_clr (struct iss_video*) ; 
 int /*<<< orphan*/  omap4iss_isp_subclk_disable (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4iss_isp_subclk_enable (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4iss_module_sync_idle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resizer_configure (struct iss_resizer_device*) ; 
 int /*<<< orphan*/  resizer_enable (struct iss_resizer_device*,int) ; 
 int /*<<< orphan*/  resizer_print_status (struct iss_resizer_device*) ; 
 struct iss_device* to_iss_device (struct iss_resizer_device*) ; 
 struct iss_resizer_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int resizer_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct iss_resizer_device *resizer = v4l2_get_subdevdata(sd);
	struct iss_device *iss = to_iss_device(resizer);
	struct iss_video *video_out = &resizer->video_out;
	int ret = 0;

	if (resizer->state == ISS_PIPELINE_STREAM_STOPPED) {
		if (enable == ISS_PIPELINE_STREAM_STOPPED)
			return 0;

		omap4iss_isp_subclk_enable(iss, OMAP4_ISS_ISP_SUBCLK_RSZ);

		iss_reg_set(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_GCK_MMR,
			    RSZ_GCK_MMR_MMR);
		iss_reg_set(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_GCK_SDR,
			    RSZ_GCK_SDR_CORE);

		/* FIXME: Enable RSZB also */
		iss_reg_set(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SYSCONFIG,
			    RSZ_SYSCONFIG_RSZA_CLK_EN);
	}

	switch (enable) {
	case ISS_PIPELINE_STREAM_CONTINUOUS:

		resizer_configure(resizer);
		resizer_print_status(resizer);

		/*
		 * When outputting to memory with no buffer available, let the
		 * buffer queue handler start the hardware. A DMA queue flag
		 * ISS_VIDEO_DMAQUEUE_QUEUED will be set as soon as there is
		 * a buffer available.
		 */
		if (resizer->output & RESIZER_OUTPUT_MEMORY &&
		    !(video_out->dmaqueue_flags & ISS_VIDEO_DMAQUEUE_QUEUED))
			break;

		atomic_set(&resizer->stopping, 0);
		resizer_enable(resizer, 1);
		iss_video_dmaqueue_flags_clr(video_out);
		break;

	case ISS_PIPELINE_STREAM_STOPPED:
		if (resizer->state == ISS_PIPELINE_STREAM_STOPPED)
			return 0;
		if (omap4iss_module_sync_idle(&sd->entity, &resizer->wait,
					      &resizer->stopping))
			ret = -ETIMEDOUT;

		resizer_enable(resizer, 0);
		iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_SYSCONFIG,
			    RSZ_SYSCONFIG_RSZA_CLK_EN);
		iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_GCK_SDR,
			    RSZ_GCK_SDR_CORE);
		iss_reg_clr(iss, OMAP4_ISS_MEM_ISP_RESIZER, RSZ_GCK_MMR,
			    RSZ_GCK_MMR_MMR);
		omap4iss_isp_subclk_disable(iss, OMAP4_ISS_ISP_SUBCLK_RSZ);
		iss_video_dmaqueue_flags_clr(video_out);
		break;
	}

	resizer->state = enable;
	return ret;
}