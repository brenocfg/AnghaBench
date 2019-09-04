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
typedef  struct vpfe_ipipe_rgb2rgb {int /*<<< orphan*/  coef_bb; int /*<<< orphan*/  coef_gb; int /*<<< orphan*/  coef_rb; int /*<<< orphan*/  coef_bg; int /*<<< orphan*/  coef_gg; int /*<<< orphan*/  coef_rg; int /*<<< orphan*/  coef_br; int /*<<< orphan*/  coef_gr; int /*<<< orphan*/  coef_rr; } const vpfe_ipipe_rgb2rgb ;
struct TYPE_6__ {struct vpfe_ipipe_rgb2rgb const rgb2rgb2; struct vpfe_ipipe_rgb2rgb const rgb2rgb1; } ;
struct TYPE_5__ {TYPE_1__* v4l2_dev; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  base_addr; TYPE_3__ config; TYPE_2__ subdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IPIPE_RGB2RGB_2 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ipipe_set_rgb2rgb_regs (int /*<<< orphan*/ ,unsigned int,struct vpfe_ipipe_rgb2rgb const*) ; 
 scalar_t__ ipipe_validate_rgb2rgb_params (struct vpfe_ipipe_rgb2rgb const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_rgb2rgb const*,struct vpfe_ipipe_rgb2rgb const*,int) ; 

__attribute__((used)) static int ipipe_set_rgb2rgb_params(struct vpfe_ipipe_device *ipipe,
			      unsigned int id, void *param)
{
	struct vpfe_ipipe_rgb2rgb *rgb2rgb = &ipipe->config.rgb2rgb1;
	struct device *dev = ipipe->subdev.v4l2_dev->dev;
	struct vpfe_ipipe_rgb2rgb *rgb2rgb_param;

	rgb2rgb_param = param;

	if (id == IPIPE_RGB2RGB_2)
		rgb2rgb = &ipipe->config.rgb2rgb2;

	if (!rgb2rgb_param) {
		const struct vpfe_ipipe_rgb2rgb rgb2rgb_defaults = {
			.coef_rr = {1, 0},	/* 256 */
			.coef_gr = {0, 0},
			.coef_br = {0, 0},
			.coef_rg = {0, 0},
			.coef_gg = {1, 0},	/* 256 */
			.coef_bg = {0, 0},
			.coef_rb = {0, 0},
			.coef_gb = {0, 0},
			.coef_bb = {1, 0},	/* 256 */
		};
		/* Copy defaults for rgb2rgb conversion */
		memcpy(rgb2rgb, &rgb2rgb_defaults,
		       sizeof(struct vpfe_ipipe_rgb2rgb));
		goto success;
	}

	memcpy(rgb2rgb, rgb2rgb_param, sizeof(struct vpfe_ipipe_rgb2rgb));
	if (ipipe_validate_rgb2rgb_params(rgb2rgb, id) < 0) {
		dev_err(dev, "Invalid rgb2rgb params\n");
		return -EINVAL;
	}

success:
	ipipe_set_rgb2rgb_regs(ipipe->base_addr, id, rgb2rgb);

	return 0;
}