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
struct vpfe_ipipe_otfdpc {int dummy; } ;
struct TYPE_6__ {TYPE_2__* v4l2_dev; } ;
struct TYPE_4__ {struct vpfe_ipipe_otfdpc otfdpc; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  base_addr; TYPE_3__ subdev; TYPE_1__ config; } ;
struct ipipe_otfdpc_2_0 {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ipipe_set_otfdpc_regs (int /*<<< orphan*/ ,struct vpfe_ipipe_otfdpc*) ; 
 scalar_t__ ipipe_validate_otfdpc_params (struct vpfe_ipipe_otfdpc*) ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_otfdpc*,struct vpfe_ipipe_otfdpc*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipipe_set_otfdpc_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_otfdpc *dpc_param = param;
	struct vpfe_ipipe_otfdpc *otfdpc = &ipipe->config.otfdpc;
	struct device *dev;

	if (!param) {
		memset((void *)otfdpc, 0, sizeof(struct ipipe_otfdpc_2_0));
		goto success;
	}
	dev = ipipe->subdev.v4l2_dev->dev;
	memcpy(otfdpc, dpc_param, sizeof(struct vpfe_ipipe_otfdpc));
	if (ipipe_validate_otfdpc_params(otfdpc) < 0) {
		dev_err(dev, "Invalid otfdpc params\n");
		return -EINVAL;
	}

success:
	ipipe_set_otfdpc_regs(ipipe->base_addr, otfdpc);

	return 0;
}