#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  struct vpfe_ipipe_wb {int /*<<< orphan*/  gain_b; int /*<<< orphan*/  gain_gb; int /*<<< orphan*/  gain_gr; int /*<<< orphan*/  gain_r; } const vpfe_ipipe_wb ;
struct TYPE_2__ {struct vpfe_ipipe_wb const wbal; } ;
struct vpfe_ipipe_device {int /*<<< orphan*/  base_addr; TYPE_1__ config; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ipipe_set_wb_regs (int /*<<< orphan*/ ,struct vpfe_ipipe_wb const*) ; 
 scalar_t__ ipipe_validate_wb_params (struct vpfe_ipipe_wb const*) ; 
 int /*<<< orphan*/  memcpy (struct vpfe_ipipe_wb const*,struct vpfe_ipipe_wb const*,int) ; 

__attribute__((used)) static int ipipe_set_wb_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_wb *wb_param = param;
	struct vpfe_ipipe_wb *wbal = &ipipe->config.wbal;

	if (!wb_param) {
		const struct vpfe_ipipe_wb wb_defaults = {
			.gain_r  = {2, 0x0},
			.gain_gr = {2, 0x0},
			.gain_gb = {2, 0x0},
			.gain_b  = {2, 0x0}
		};
		memcpy(wbal, &wb_defaults, sizeof(struct vpfe_ipipe_wb));
		goto success;
	}

	memcpy(wbal, wb_param, sizeof(struct vpfe_ipipe_wb));
	if (ipipe_validate_wb_params(wbal) < 0)
		return -EINVAL;

success:
	ipipe_set_wb_regs(ipipe->base_addr, wbal);

	return 0;
}