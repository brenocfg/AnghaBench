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
struct vpfe_ipipe_yee {int dummy; } ;
struct TYPE_6__ {struct vpfe_ipipe_yee yee; } ;
struct TYPE_5__ {TYPE_1__* v4l2_dev; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  isp5_base_addr; int /*<<< orphan*/  base_addr; TYPE_3__ config; TYPE_2__ subdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ipipe_set_ee_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vpfe_ipipe_yee*) ; 
 scalar_t__ ipipe_validate_yee_params (struct vpfe_ipipe_yee*) ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_yee*,struct vpfe_ipipe_yee*,int) ; 
 int /*<<< orphan*/  memset (struct vpfe_ipipe_yee*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipipe_set_yee_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_yee *yee_param = param;
	struct device *dev = ipipe->subdev.v4l2_dev->dev;
	struct vpfe_ipipe_yee *yee = &ipipe->config.yee;

	if (!yee_param) {
		memset(yee, 0, sizeof(struct vpfe_ipipe_yee));
	} else {
		memcpy(yee, yee_param, sizeof(struct vpfe_ipipe_yee));
		if (ipipe_validate_yee_params(yee) < 0) {
			dev_err(dev, "Invalid yee params\n");
			return -EINVAL;
		}
	}

	ipipe_set_ee_regs(ipipe->base_addr, ipipe->isp5_base_addr, yee);

	return 0;
}