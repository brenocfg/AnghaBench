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
struct vpfe_ipipe_nf {int dummy; } ;
struct TYPE_5__ {TYPE_1__* v4l2_dev; } ;
struct TYPE_6__ {struct vpfe_ipipe_nf nf2; struct vpfe_ipipe_nf nf1; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  base_addr; TYPE_2__ subdev; TYPE_3__ config; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IPIPE_D2F_2ND ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ipipe_set_d2f_regs (int /*<<< orphan*/ ,unsigned int,struct vpfe_ipipe_nf*) ; 
 scalar_t__ ipipe_validate_nf_params (struct vpfe_ipipe_nf*) ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_nf*,struct vpfe_ipipe_nf*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipipe_set_nf_params(struct vpfe_ipipe_device *ipipe,
			       unsigned int id, void *param)
{
	struct vpfe_ipipe_nf *nf_param = param;
	struct vpfe_ipipe_nf *nf = &ipipe->config.nf1;
	struct device *dev;

	if (id == IPIPE_D2F_2ND)
		nf = &ipipe->config.nf2;

	if (!nf_param) {
		memset((void *)nf, 0, sizeof(struct vpfe_ipipe_nf));
		goto success;
	}

	dev = ipipe->subdev.v4l2_dev->dev;
	memcpy(nf, nf_param, sizeof(struct vpfe_ipipe_nf));
	if (ipipe_validate_nf_params(nf) < 0) {
		dev_err(dev, "Invalid nf params\n");
		return -EINVAL;
	}

success:
	ipipe_set_d2f_regs(ipipe->base_addr, id, nf);

	return 0;
}