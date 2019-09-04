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
typedef  int u32 ;
struct rproc {scalar_t__ priv; } ;
struct q6v5 {int running; scalar_t__ version; int /*<<< orphan*/  active_reg_count; int /*<<< orphan*/  active_regs; int /*<<< orphan*/  active_clk_count; int /*<<< orphan*/  active_clks; int /*<<< orphan*/  dev; int /*<<< orphan*/  reset_clk_count; int /*<<< orphan*/  reset_clks; int /*<<< orphan*/  proxy_reg_count; int /*<<< orphan*/  proxy_regs; int /*<<< orphan*/  proxy_clk_count; int /*<<< orphan*/  proxy_clks; int /*<<< orphan*/  q6v5; int /*<<< orphan*/  mpss_size; int /*<<< orphan*/  mpss_phys; int /*<<< orphan*/  mpss_perm; scalar_t__ reg_base; int /*<<< orphan*/  halt_nc; int /*<<< orphan*/  halt_map; int /*<<< orphan*/  halt_modem; int /*<<< orphan*/  halt_q6; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ MSS_MSM8996 ; 
 int Q6SS_CLAMP_IO ; 
 scalar_t__ QDSP6SS_PWR_CTL_REG ; 
 int QDSP6v56_CLAMP_QMC_MEM ; 
 int QDSP6v56_CLAMP_WL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  q6v5_clk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6v5_regulator_disable (struct q6v5*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6v5_reset_assert (struct q6v5*) ; 
 int q6v5_xfer_mem_ownership (struct q6v5*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6v5proc_halt_axi_port (struct q6v5*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qcom_q6v5_request_stop (int /*<<< orphan*/ *) ; 
 int qcom_q6v5_unprepare (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int q6v5_stop(struct rproc *rproc)
{
	struct q6v5 *qproc = (struct q6v5 *)rproc->priv;
	int ret;
	u32 val;

	qproc->running = false;

	ret = qcom_q6v5_request_stop(&qproc->q6v5);
	if (ret == -ETIMEDOUT)
		dev_err(qproc->dev, "timed out on wait\n");

	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_q6);
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_modem);
	q6v5proc_halt_axi_port(qproc, qproc->halt_map, qproc->halt_nc);
	if (qproc->version == MSS_MSM8996) {
		/*
		 * To avoid high MX current during LPASS/MSS restart.
		 */
		val = readl(qproc->reg_base + QDSP6SS_PWR_CTL_REG);
		val |= Q6SS_CLAMP_IO | QDSP6v56_CLAMP_WL |
			QDSP6v56_CLAMP_QMC_MEM;
		writel(val, qproc->reg_base + QDSP6SS_PWR_CTL_REG);
	}


	ret = q6v5_xfer_mem_ownership(qproc, &qproc->mpss_perm, false,
				      qproc->mpss_phys, qproc->mpss_size);
	WARN_ON(ret);

	q6v5_reset_assert(qproc);

	ret = qcom_q6v5_unprepare(&qproc->q6v5);
	if (ret) {
		q6v5_clk_disable(qproc->dev, qproc->proxy_clks,
				 qproc->proxy_clk_count);
		q6v5_regulator_disable(qproc, qproc->proxy_regs,
				       qproc->proxy_reg_count);
	}

	q6v5_clk_disable(qproc->dev, qproc->reset_clks,
			 qproc->reset_clk_count);
	q6v5_clk_disable(qproc->dev, qproc->active_clks,
			 qproc->active_clk_count);
	q6v5_regulator_disable(qproc, qproc->active_regs,
			       qproc->active_reg_count);

	return 0;
}