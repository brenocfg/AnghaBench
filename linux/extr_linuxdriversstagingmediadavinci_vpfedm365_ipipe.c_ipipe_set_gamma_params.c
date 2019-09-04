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
struct vpfe_ipipe_gamma {scalar_t__ tbl_sel; int tbl_size; int /*<<< orphan*/  table_g; int /*<<< orphan*/  bypass_g; int /*<<< orphan*/  table_b; int /*<<< orphan*/  bypass_b; int /*<<< orphan*/  table_r; int /*<<< orphan*/  bypass_r; } ;
struct TYPE_6__ {TYPE_2__* v4l2_dev; } ;
struct TYPE_4__ {struct vpfe_ipipe_gamma gamma; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  isp5_base_addr; int /*<<< orphan*/  base_addr; TYPE_3__ subdev; TYPE_1__ config; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VPFE_IPIPE_GAMMA_TBL_RAM ; 
 scalar_t__ VPFE_IPIPE_GAMMA_TBL_ROM ; 
 int /*<<< orphan*/  ipipe_set_gamma_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vpfe_ipipe_gamma*) ; 
 scalar_t__ ipipe_validate_gamma_params (struct vpfe_ipipe_gamma*,struct device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct vpfe_ipipe_gamma*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ipipe_set_gamma_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_gamma *gamma_param = param;
	struct vpfe_ipipe_gamma *gamma = &ipipe->config.gamma;
	struct device *dev = ipipe->subdev.v4l2_dev->dev;
	int table_size;

	if (!gamma_param) {
		memset(gamma, 0, sizeof(struct vpfe_ipipe_gamma));
		gamma->tbl_sel = VPFE_IPIPE_GAMMA_TBL_ROM;
		goto success;
	}

	gamma->bypass_r = gamma_param->bypass_r;
	gamma->bypass_b = gamma_param->bypass_b;
	gamma->bypass_g = gamma_param->bypass_g;
	gamma->tbl_sel = gamma_param->tbl_sel;
	gamma->tbl_size = gamma_param->tbl_size;

	if (ipipe_validate_gamma_params(gamma, dev) < 0)
		return -EINVAL;

	if (gamma_param->tbl_sel != VPFE_IPIPE_GAMMA_TBL_RAM)
		goto success;

	table_size = gamma->tbl_size;
	if (!gamma_param->bypass_r)
		memcpy(&gamma->table_r, &gamma_param->table_r,
		       (table_size * sizeof(struct vpfe_ipipe_gamma_entry)));

	if (!gamma_param->bypass_b)
		memcpy(&gamma->table_b, &gamma_param->table_b,
		       (table_size * sizeof(struct vpfe_ipipe_gamma_entry)));

	if (!gamma_param->bypass_g)
		memcpy(&gamma->table_g, &gamma_param->table_g,
		       (table_size * sizeof(struct vpfe_ipipe_gamma_entry)));

success:
	ipipe_set_gamma_regs(ipipe->base_addr, ipipe->isp5_base_addr, gamma);

	return 0;
}