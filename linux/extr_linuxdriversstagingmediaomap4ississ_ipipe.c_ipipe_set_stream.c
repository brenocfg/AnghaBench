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
struct iss_ipipe_device {int state; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; } ;
struct iss_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IPIPE_GCK_MMR ; 
 int IPIPE_GCK_MMR_REG ; 
 int /*<<< orphan*/  IPIPE_GCK_PIX ; 
 int IPIPE_GCK_PIX_G0 ; 
 int IPIPE_GCK_PIX_G1 ; 
 int IPIPE_GCK_PIX_G2 ; 
 int IPIPE_GCK_PIX_G3 ; 
#define  ISS_PIPELINE_STREAM_CONTINUOUS 129 
#define  ISS_PIPELINE_STREAM_STOPPED 128 
 int /*<<< orphan*/  OMAP4_ISS_ISP_SUBCLK_IPIPE ; 
 int /*<<< orphan*/  OMAP4_ISS_MEM_ISP_IPIPE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipipe_configure (struct iss_ipipe_device*) ; 
 int /*<<< orphan*/  ipipe_enable (struct iss_ipipe_device*,int) ; 
 int /*<<< orphan*/  ipipe_print_status (struct iss_ipipe_device*) ; 
 int /*<<< orphan*/  iss_reg_write (struct iss_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  omap4iss_isp_subclk_disable (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4iss_isp_subclk_enable (struct iss_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4iss_module_sync_idle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct iss_device* to_iss_device (struct iss_ipipe_device*) ; 
 struct iss_ipipe_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ipipe_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct iss_ipipe_device *ipipe = v4l2_get_subdevdata(sd);
	struct iss_device *iss = to_iss_device(ipipe);
	int ret = 0;

	if (ipipe->state == ISS_PIPELINE_STREAM_STOPPED) {
		if (enable == ISS_PIPELINE_STREAM_STOPPED)
			return 0;

		omap4iss_isp_subclk_enable(iss, OMAP4_ISS_ISP_SUBCLK_IPIPE);

		/* Enable clk_arm_g0 */
		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_GCK_MMR,
			      IPIPE_GCK_MMR_REG);

		/* Enable clk_pix_g[3:0] */
		iss_reg_write(iss, OMAP4_ISS_MEM_ISP_IPIPE, IPIPE_GCK_PIX,
			      IPIPE_GCK_PIX_G3 | IPIPE_GCK_PIX_G2 |
			      IPIPE_GCK_PIX_G1 | IPIPE_GCK_PIX_G0);
	}

	switch (enable) {
	case ISS_PIPELINE_STREAM_CONTINUOUS:

		ipipe_configure(ipipe);
		ipipe_print_status(ipipe);

		atomic_set(&ipipe->stopping, 0);
		ipipe_enable(ipipe, 1);
		break;

	case ISS_PIPELINE_STREAM_STOPPED:
		if (ipipe->state == ISS_PIPELINE_STREAM_STOPPED)
			return 0;
		if (omap4iss_module_sync_idle(&sd->entity, &ipipe->wait,
					      &ipipe->stopping))
			ret = -ETIMEDOUT;

		ipipe_enable(ipipe, 0);
		omap4iss_isp_subclk_disable(iss, OMAP4_ISS_ISP_SUBCLK_IPIPE);
		break;
	}

	ipipe->state = enable;
	return ret;
}