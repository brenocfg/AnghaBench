#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rproc {scalar_t__ priv; } ;
struct q6v5 {int running; int /*<<< orphan*/  q6v5; int /*<<< orphan*/  proxy_reg_count; int /*<<< orphan*/  proxy_regs; int /*<<< orphan*/  proxy_clk_count; int /*<<< orphan*/  proxy_clks; int /*<<< orphan*/  dev; int /*<<< orphan*/  active_reg_count; int /*<<< orphan*/  active_regs; int /*<<< orphan*/  reset_clk_count; int /*<<< orphan*/  reset_clks; int /*<<< orphan*/  active_clk_count; int /*<<< orphan*/  active_clks; int /*<<< orphan*/  mba_size; int /*<<< orphan*/  mba_phys; int /*<<< orphan*/  mba_perm; int /*<<< orphan*/  halt_nc; int /*<<< orphan*/  halt_map; int /*<<< orphan*/  halt_modem; int /*<<< orphan*/  halt_q6; int /*<<< orphan*/  mpss_size; int /*<<< orphan*/  mpss_phys; int /*<<< orphan*/  mpss_perm; scalar_t__ rmb_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ RMB_MBA_IMAGE_REG ; 
 int RMB_MBA_XPU_UNLOCKED ; 
 int RMB_MBA_XPU_UNLOCKED_SCRIBBLED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  q6v5_clk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int q6v5_clk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int q6v5_mpss_load (struct q6v5*) ; 
 int /*<<< orphan*/  q6v5_regulator_disable (struct q6v5*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int q6v5_regulator_enable (struct q6v5*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6v5_reset_assert (struct q6v5*) ; 
 int q6v5_reset_deassert (struct q6v5*) ; 
 int q6v5_rmb_mba_wait (struct q6v5*,int /*<<< orphan*/ ,int) ; 
 int q6v5_xfer_mem_ownership (struct q6v5*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6v5proc_halt_axi_port (struct q6v5*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int q6v5proc_reset (struct q6v5*) ; 
 int /*<<< orphan*/  qcom_q6v5_prepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_q6v5_unprepare (int /*<<< orphan*/ *) ; 
 int qcom_q6v5_wait_for_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int q6v5_start(struct rproc *rproc)
{
	struct q6v5 *qproc = (struct q6v5 *)rproc->priv;
	int xfermemop_ret;
	int ret;

	qcom_q6v5_prepare(&qproc->q6v5);

	ret = q6v5_regulator_enable(qproc, qproc->proxy_regs,
				    qproc->proxy_reg_count);
	if (ret) {
		dev_err(qproc->dev, "failed to enable proxy supplies\n");
		goto disable_irqs;
	}

	ret = q6v5_clk_enable(qproc->dev, qproc->proxy_clks,
			      qproc->proxy_clk_count);
	if (ret) {
		dev_err(qproc->dev, "failed to enable proxy clocks\n");
		goto disable_proxy_reg;
	}

	ret = q6v5_regulator_enable(qproc, qproc->active_regs,
				    qproc->active_reg_count);
	if (ret) {
		dev_err(qproc->dev, "failed to enable supplies\n");
		goto disable_proxy_clk;
	}

	ret = q6v5_clk_enable(qproc->dev, qproc->reset_clks,
			      qproc->reset_clk_count);
	if (ret) {
		dev_err(qproc->dev, "failed to enable reset clocks\n");
		goto disable_vdd;
	}

	ret = q6v5_reset_deassert(qproc);
	if (ret) {
		dev_err(qproc->dev, "failed to deassert mss restart\n");
		goto disable_reset_clks;
	}

	ret = q6v5_clk_enable(qproc->dev, qproc->active_clks,
			      qproc->active_clk_count);
	if (ret) {
		dev_err(qproc->dev, "failed to enable clocks\n");
		goto assert_reset;
	}

	/* Assign MBA image access in DDR to q6 */
	ret = q6v5_xfer_mem_ownership(qproc, &qproc->mba_perm, true,
				      qproc->mba_phys, qproc->mba_size);
	if (ret) {
		dev_err(qproc->dev,
			"assigning Q6 access to mba memory failed: %d\n", ret);
		goto disable_active_clks;
	}

	writel(qproc->mba_phys, qproc->rmb_base + RMB_MBA_IMAGE_REG);

	ret = q6v5proc_reset(qproc);
	if (ret)
		goto reclaim_mba;

	ret = q6v5_rmb_mba_wait(qproc, 0, 5000);
	if (ret == -ETIMEDOUT) {
		dev_err(qproc->dev, "MBA boot timed out\n");
		goto halt_axi_ports;
	} else if (ret != RMB_MBA_XPU_UNLOCKED &&
		   ret != RMB_MBA_XPU_UNLOCKED_SCRIBBLED) {
		dev_err(qproc->dev, "MBA returned unexpected status %d\n", ret);
		ret = -EINVAL;
		goto halt_axi_ports;
	}

	dev_info(qproc->dev, "MBA booted, loading mpss\n");

	ret = q6v5_mpss_load(qproc);
	if (ret)
		goto reclaim_mpss;

	ret = qcom_q6v5_wait_for_start(&qproc->q6v5, msecs_to_jiffies(5000));
	if (ret == -ETIMEDOUT) {
		dev_err(qproc->dev, "start timed out\n");
		goto reclaim_mpss;
	}

	xfermemop_ret = q6v5_xfer_mem_ownership(qproc, &qproc->mba_perm, false,
						qproc->mba_phys,
						qproc->mba_size);
	if (xfermemop_ret)
		dev_err(qproc->dev,
			"Failed to reclaim mba buffer system may become unstable\n");
	qproc->running = true;

	return 0;

reclaim_mpss:
	xfermemop_ret = q6v5_xfer_mem_ownership(qproc, &qproc->mpss_perm,
						false, qproc->mpss_phys,
						qproc->mpss_size);
	WARN_ON(xfermemop_ret);

halt_axi_ports:
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_q6);
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_modem);
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_nc);

reclaim_mba:
	xfermemop_ret = q6v5_xfer_mem_ownership(qproc, &qproc->mba_perm, false,
						qproc->mba_phys,
						qproc->mba_size);
	if (xfermemop_ret) {
		dev_err(qproc->dev,
			"Failed to reclaim mba buffer, system may become unstable\n");
	}

disable_active_clks:
	q6v5_clk_disable(qproc->dev, qproc->active_clks,
			 qproc->active_clk_count);

assert_reset:
	q6v5_reset_assert(qproc);
disable_reset_clks:
	q6v5_clk_disable(qproc->dev, qproc->reset_clks,
			 qproc->reset_clk_count);
disable_vdd:
	q6v5_regulator_disable(qproc, qproc->active_regs,
			       qproc->active_reg_count);
disable_proxy_clk:
	q6v5_clk_disable(qproc->dev, qproc->proxy_clks,
			 qproc->proxy_clk_count);
disable_proxy_reg:
	q6v5_regulator_disable(qproc, qproc->proxy_regs,
			       qproc->proxy_reg_count);

disable_irqs:
	qcom_q6v5_unprepare(&qproc->q6v5);

	return ret;
}