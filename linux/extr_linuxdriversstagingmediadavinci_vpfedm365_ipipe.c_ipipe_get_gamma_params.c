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
struct vpfe_ipipe_gamma_entry {int dummy; } ;
struct vpfe_ipipe_gamma {scalar_t__ tbl_sel; int tbl_size; int /*<<< orphan*/  table_b; int /*<<< orphan*/  bypass_b; int /*<<< orphan*/  table_g; int /*<<< orphan*/  bypass_g; int /*<<< orphan*/  table_r; int /*<<< orphan*/  bypass_r; } ;
struct TYPE_6__ {TYPE_2__* v4l2_dev; } ;
struct TYPE_4__ {struct vpfe_ipipe_gamma gamma; } ;
struct vpfe_ipipe_device {TYPE_3__ subdev; TYPE_1__ config; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VPFE_IPIPE_GAMMA_TBL_RAM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipipe_get_gamma_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_gamma *gamma_param = param;
	struct vpfe_ipipe_gamma *gamma = &ipipe->config.gamma;
	struct device *dev = ipipe->subdev.v4l2_dev->dev;
	int table_size;

	gamma_param->bypass_r = gamma->bypass_r;
	gamma_param->bypass_g = gamma->bypass_g;
	gamma_param->bypass_b = gamma->bypass_b;
	gamma_param->tbl_sel = gamma->tbl_sel;
	gamma_param->tbl_size = gamma->tbl_size;

	if (gamma->tbl_sel != VPFE_IPIPE_GAMMA_TBL_RAM)
		return 0;

	table_size = gamma->tbl_size;

	if (!gamma->bypass_r) {
		dev_err(dev,
			"ipipe_get_gamma_params: table ptr empty for R\n");
		return -EINVAL;
	}
	memcpy(gamma_param->table_r, gamma->table_r,
	       (table_size * sizeof(struct vpfe_ipipe_gamma_entry)));

	if (!gamma->bypass_g) {
		dev_err(dev, "ipipe_get_gamma_params: table ptr empty for G\n");
		return -EINVAL;
	}
	memcpy(gamma_param->table_g, gamma->table_g,
	       (table_size * sizeof(struct vpfe_ipipe_gamma_entry)));

	if (!gamma->bypass_b) {
		dev_err(dev, "ipipe_get_gamma_params: table ptr empty for B\n");
		return -EINVAL;
	}
	memcpy(gamma_param->table_b, gamma->table_b,
	       (table_size * sizeof(struct vpfe_ipipe_gamma_entry)));

	return 0;
}