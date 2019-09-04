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
typedef  struct vpfe_ipipe_rgb2yuv {int out_ofst_cb; int out_ofst_cr; int /*<<< orphan*/  coef_bcr; int /*<<< orphan*/  coef_gcr; int /*<<< orphan*/  coef_rcr; int /*<<< orphan*/  coef_bcb; int /*<<< orphan*/  coef_gcb; int /*<<< orphan*/  coef_rcb; int /*<<< orphan*/  coef_by; int /*<<< orphan*/  coef_gy; int /*<<< orphan*/  coef_ry; } const vpfe_ipipe_rgb2yuv ;
struct TYPE_4__ {TYPE_3__* v4l2_dev; } ;
struct TYPE_5__ {struct vpfe_ipipe_rgb2yuv const rgb2yuv; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  base_addr; TYPE_1__ subdev; TYPE_2__ config; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ipipe_set_rgb2ycbcr_regs (int /*<<< orphan*/ ,struct vpfe_ipipe_rgb2yuv const*) ; 
 scalar_t__ ipipe_validate_rgb2yuv_params (struct vpfe_ipipe_rgb2yuv const*) ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_rgb2yuv const*,struct vpfe_ipipe_rgb2yuv const*,int) ; 

__attribute__((used)) static int
ipipe_set_rgb2yuv_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_rgb2yuv *rgb2yuv = &ipipe->config.rgb2yuv;
	struct device *dev = ipipe->subdev.v4l2_dev->dev;
	struct vpfe_ipipe_rgb2yuv *rgb2yuv_param;

	rgb2yuv_param = param;
	if (!rgb2yuv_param) {
		/* Defaults for rgb2yuv conversion */
		const struct vpfe_ipipe_rgb2yuv rgb2yuv_defaults = {
			.coef_ry  = {0, 0x4d},
			.coef_gy  = {0, 0x96},
			.coef_by  = {0, 0x1d},
			.coef_rcb = {0xf, 0xd5},
			.coef_gcb = {0xf, 0xab},
			.coef_bcb = {0, 0x80},
			.coef_rcr = {0, 0x80},
			.coef_gcr = {0xf, 0x95},
			.coef_bcr = {0xf, 0xeb},
			.out_ofst_cb = 0x80,
			.out_ofst_cr = 0x80,
		};
		/* Copy defaults for rgb2yuv conversion  */
		memcpy(rgb2yuv, &rgb2yuv_defaults,
		       sizeof(struct vpfe_ipipe_rgb2yuv));
		goto success;
	}

	memcpy(rgb2yuv, rgb2yuv_param, sizeof(struct vpfe_ipipe_rgb2yuv));
	if (ipipe_validate_rgb2yuv_params(rgb2yuv) < 0) {
		dev_err(dev, "Invalid rgb2yuv params\n");
		return -EINVAL;
	}

success:
	ipipe_set_rgb2ycbcr_regs(ipipe->base_addr, rgb2yuv);

	return 0;
}