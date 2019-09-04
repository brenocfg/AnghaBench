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
struct vpfe_ipipe_yuv422_conv {int /*<<< orphan*/  chrom_pos; } ;
struct TYPE_6__ {TYPE_2__* v4l2_dev; } ;
struct TYPE_4__ {struct vpfe_ipipe_yuv422_conv yuv422_conv; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  base_addr; TYPE_3__ subdev; TYPE_1__ config; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VPFE_IPIPE_YUV422_CHR_POS_COSITE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ipipe_set_yuv422_conv_regs (int /*<<< orphan*/ ,struct vpfe_ipipe_yuv422_conv*) ; 
 scalar_t__ ipipe_validate_yuv422_conv_params (struct vpfe_ipipe_yuv422_conv*) ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_yuv422_conv*,struct vpfe_ipipe_yuv422_conv*,int) ; 
 int /*<<< orphan*/  memset (struct vpfe_ipipe_yuv422_conv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ipipe_set_yuv422_conv_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_yuv422_conv *yuv422_conv = &ipipe->config.yuv422_conv;
	struct vpfe_ipipe_yuv422_conv *yuv422_conv_param;
	struct device *dev = ipipe->subdev.v4l2_dev->dev;

	yuv422_conv_param = param;
	if (!yuv422_conv_param) {
		memset(yuv422_conv, 0, sizeof(struct vpfe_ipipe_yuv422_conv));
		yuv422_conv->chrom_pos = VPFE_IPIPE_YUV422_CHR_POS_COSITE;
	} else {
		memcpy(yuv422_conv, yuv422_conv_param,
			sizeof(struct vpfe_ipipe_yuv422_conv));
		if (ipipe_validate_yuv422_conv_params(yuv422_conv) < 0) {
			dev_err(dev, "Invalid yuv422 params\n");
			return -EINVAL;
		}
	}

	ipipe_set_yuv422_conv_regs(ipipe->base_addr, yuv422_conv);

	return 0;
}