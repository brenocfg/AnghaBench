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
struct rproc_hexagon_res {int /*<<< orphan*/  need_mem_protection; int /*<<< orphan*/  has_alt_reset; int /*<<< orphan*/  version; int /*<<< orphan*/  active_supply; int /*<<< orphan*/  proxy_supply; int /*<<< orphan*/  active_clk_names; int /*<<< orphan*/  reset_clk_names; int /*<<< orphan*/  proxy_clk_names; int /*<<< orphan*/  hexagon_mba_image; } ;
struct rproc {scalar_t__ priv; } ;
struct q6v5 {int proxy_clk_count; int reset_clk_count; int active_clk_count; int proxy_reg_count; int active_reg_count; int /*<<< orphan*/  sysmon; int /*<<< orphan*/  ssr_subdev; int /*<<< orphan*/  smd_subdev; int /*<<< orphan*/  glink_subdev; void* mba_perm; void* mpss_perm; int /*<<< orphan*/  q6v5; int /*<<< orphan*/  need_mem_protection; int /*<<< orphan*/  has_alt_reset; int /*<<< orphan*/  version; int /*<<< orphan*/  active_regs; int /*<<< orphan*/  proxy_regs; int /*<<< orphan*/  active_clks; int /*<<< orphan*/  reset_clks; int /*<<< orphan*/  proxy_clks; struct rproc* rproc; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 void* BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MPSS_CRASH_REASON_SMEM ; 
 int /*<<< orphan*/  QCOM_SCM_VMID_HLOS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct rproc_hexagon_res* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct q6v5*) ; 
 int q6v5_alloc_memory_region (struct q6v5*) ; 
 int q6v5_init_clocks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int q6v5_init_mem (struct q6v5*,struct platform_device*) ; 
 int q6v5_init_reset (struct q6v5*) ; 
 int /*<<< orphan*/  q6v5_ops ; 
 int q6v5_regulator_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_add_glink_subdev (struct rproc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_add_smd_subdev (struct rproc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_add_ssr_subdev (struct rproc*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qcom_add_sysmon_subdev (struct rproc*,char*,int) ; 
 int /*<<< orphan*/  qcom_msa_handover ; 
 int qcom_q6v5_init (int /*<<< orphan*/ *,struct platform_device*,struct rproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rproc_add (struct rproc*) ; 
 struct rproc* rproc_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rproc_free (struct rproc*) ; 

__attribute__((used)) static int q6v5_probe(struct platform_device *pdev)
{
	const struct rproc_hexagon_res *desc;
	struct q6v5 *qproc;
	struct rproc *rproc;
	int ret;

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		return -EINVAL;

	rproc = rproc_alloc(&pdev->dev, pdev->name, &q6v5_ops,
			    desc->hexagon_mba_image, sizeof(*qproc));
	if (!rproc) {
		dev_err(&pdev->dev, "failed to allocate rproc\n");
		return -ENOMEM;
	}

	qproc = (struct q6v5 *)rproc->priv;
	qproc->dev = &pdev->dev;
	qproc->rproc = rproc;
	platform_set_drvdata(pdev, qproc);

	ret = q6v5_init_mem(qproc, pdev);
	if (ret)
		goto free_rproc;

	ret = q6v5_alloc_memory_region(qproc);
	if (ret)
		goto free_rproc;

	ret = q6v5_init_clocks(&pdev->dev, qproc->proxy_clks,
			       desc->proxy_clk_names);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to get proxy clocks.\n");
		goto free_rproc;
	}
	qproc->proxy_clk_count = ret;

	ret = q6v5_init_clocks(&pdev->dev, qproc->reset_clks,
			       desc->reset_clk_names);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to get reset clocks.\n");
		goto free_rproc;
	}
	qproc->reset_clk_count = ret;

	ret = q6v5_init_clocks(&pdev->dev, qproc->active_clks,
			       desc->active_clk_names);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to get active clocks.\n");
		goto free_rproc;
	}
	qproc->active_clk_count = ret;

	ret = q6v5_regulator_init(&pdev->dev, qproc->proxy_regs,
				  desc->proxy_supply);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to get proxy regulators.\n");
		goto free_rproc;
	}
	qproc->proxy_reg_count = ret;

	ret = q6v5_regulator_init(&pdev->dev,  qproc->active_regs,
				  desc->active_supply);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to get active regulators.\n");
		goto free_rproc;
	}
	qproc->active_reg_count = ret;

	ret = q6v5_init_reset(qproc);
	if (ret)
		goto free_rproc;

	qproc->version = desc->version;
	qproc->has_alt_reset = desc->has_alt_reset;
	qproc->need_mem_protection = desc->need_mem_protection;

	ret = qcom_q6v5_init(&qproc->q6v5, pdev, rproc, MPSS_CRASH_REASON_SMEM,
			     qcom_msa_handover);
	if (ret)
		goto free_rproc;

	qproc->mpss_perm = BIT(QCOM_SCM_VMID_HLOS);
	qproc->mba_perm = BIT(QCOM_SCM_VMID_HLOS);
	qcom_add_glink_subdev(rproc, &qproc->glink_subdev);
	qcom_add_smd_subdev(rproc, &qproc->smd_subdev);
	qcom_add_ssr_subdev(rproc, &qproc->ssr_subdev, "mpss");
	qproc->sysmon = qcom_add_sysmon_subdev(rproc, "modem", 0x12);

	ret = rproc_add(rproc);
	if (ret)
		goto free_rproc;

	return 0;

free_rproc:
	rproc_free(rproc);

	return ret;
}