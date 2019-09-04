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
struct st_rproc {int /*<<< orphan*/  clk; int /*<<< orphan*/  sw_reset; TYPE_1__* config; int /*<<< orphan*/  pwr_reset; int /*<<< orphan*/  boot_offset; int /*<<< orphan*/  boot_base; } ;
struct rproc {int /*<<< orphan*/  bootaddr; int /*<<< orphan*/  dev; struct st_rproc* priv; } ;
struct TYPE_2__ {scalar_t__ pwr_reset; scalar_t__ sw_reset; int /*<<< orphan*/  bootaddr_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_rproc_start(struct rproc *rproc)
{
	struct st_rproc *ddata = rproc->priv;
	int err;

	regmap_update_bits(ddata->boot_base, ddata->boot_offset,
			   ddata->config->bootaddr_mask, rproc->bootaddr);

	err = clk_enable(ddata->clk);
	if (err) {
		dev_err(&rproc->dev, "Failed to enable clock\n");
		return err;
	}

	if (ddata->config->sw_reset) {
		err = reset_control_deassert(ddata->sw_reset);
		if (err) {
			dev_err(&rproc->dev, "Failed to deassert S/W Reset\n");
			goto sw_reset_fail;
		}
	}

	if (ddata->config->pwr_reset) {
		err = reset_control_deassert(ddata->pwr_reset);
		if (err) {
			dev_err(&rproc->dev, "Failed to deassert Power Reset\n");
			goto pwr_reset_fail;
		}
	}

	dev_info(&rproc->dev, "Started from 0x%x\n", rproc->bootaddr);

	return 0;


pwr_reset_fail:
	if (ddata->config->pwr_reset)
		reset_control_assert(ddata->sw_reset);
sw_reset_fail:
	clk_disable(ddata->clk);

	return err;
}