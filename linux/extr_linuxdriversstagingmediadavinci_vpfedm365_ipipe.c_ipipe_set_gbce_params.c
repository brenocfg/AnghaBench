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
struct vpfe_ipipe_gbce {int dummy; } ;
struct TYPE_6__ {TYPE_2__* v4l2_dev; } ;
struct TYPE_4__ {struct vpfe_ipipe_gbce gbce; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  isp5_base_addr; int /*<<< orphan*/  base_addr; TYPE_3__ subdev; TYPE_1__ config; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ipipe_set_gbce_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vpfe_ipipe_gbce*) ; 
 scalar_t__ ipipe_validate_gbce_params (struct vpfe_ipipe_gbce*) ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_gbce*,struct vpfe_ipipe_gbce*,int) ; 
 int /*<<< orphan*/  memset (struct vpfe_ipipe_gbce*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipipe_set_gbce_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_gbce *gbce_param = param;
	struct vpfe_ipipe_gbce *gbce = &ipipe->config.gbce;
	struct device *dev = ipipe->subdev.v4l2_dev->dev;

	if (!gbce_param) {
		memset(gbce, 0, sizeof(struct vpfe_ipipe_gbce));
	} else {
		memcpy(gbce, gbce_param, sizeof(struct vpfe_ipipe_gbce));
		if (ipipe_validate_gbce_params(gbce) < 0) {
			dev_err(dev, "Invalid gbce params\n");
			return -EINVAL;
		}
	}

	ipipe_set_gbce_regs(ipipe->base_addr, ipipe->isp5_base_addr, gbce);

	return 0;
}