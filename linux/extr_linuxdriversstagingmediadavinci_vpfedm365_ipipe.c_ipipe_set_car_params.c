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
struct vpfe_ipipe_car {int dummy; } ;
struct TYPE_6__ {struct vpfe_ipipe_car car; } ;
struct TYPE_5__ {TYPE_1__* v4l2_dev; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  base_addr; TYPE_3__ config; TYPE_2__ subdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ipipe_set_car_regs (int /*<<< orphan*/ ,struct vpfe_ipipe_car*) ; 
 scalar_t__ ipipe_validate_car_params (struct vpfe_ipipe_car*) ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_car*,struct vpfe_ipipe_car*,int) ; 
 int /*<<< orphan*/  memset (struct vpfe_ipipe_car*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipipe_set_car_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_car *car_param = param;
	struct device *dev = ipipe->subdev.v4l2_dev->dev;
	struct vpfe_ipipe_car *car = &ipipe->config.car;

	if (!car_param) {
		memset(car, 0, sizeof(struct vpfe_ipipe_car));
	} else {
		memcpy(car, car_param, sizeof(struct vpfe_ipipe_car));
		if (ipipe_validate_car_params(car) < 0) {
			dev_err(dev, "Invalid car params\n");
			return -EINVAL;
		}
	}

	ipipe_set_car_regs(ipipe->base_addr, car);

	return 0;
}