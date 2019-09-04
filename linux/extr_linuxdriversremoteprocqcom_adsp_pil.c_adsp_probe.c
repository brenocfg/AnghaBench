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
struct qcom_adsp {int /*<<< orphan*/  sysmon; int /*<<< orphan*/  ssr_subdev; int /*<<< orphan*/  smd_subdev; int /*<<< orphan*/  glink_subdev; int /*<<< orphan*/  q6v5; int /*<<< orphan*/  has_aggre2_clk; int /*<<< orphan*/  pas_id; struct rproc* rproc; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct adsp_data {int /*<<< orphan*/  ssctl_id; int /*<<< orphan*/  sysmon_name; int /*<<< orphan*/  ssr_name; int /*<<< orphan*/  crash_reason_smem; int /*<<< orphan*/  has_aggre2_clk; int /*<<< orphan*/  pas_id; int /*<<< orphan*/  firmware_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int adsp_alloc_memory_region (struct qcom_adsp*) ; 
 int adsp_init_clock (struct qcom_adsp*) ; 
 int adsp_init_regulator (struct qcom_adsp*) ; 
 int /*<<< orphan*/  adsp_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct adsp_data* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qcom_adsp*) ; 
 int /*<<< orphan*/  qcom_add_glink_subdev (struct rproc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_add_smd_subdev (struct rproc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_add_ssr_subdev (struct rproc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_add_sysmon_subdev (struct rproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_pas_handover ; 
 int qcom_q6v5_init (int /*<<< orphan*/ *,struct platform_device*,struct rproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_scm_is_available () ; 
 int rproc_add (struct rproc*) ; 
 struct rproc* rproc_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rproc_free (struct rproc*) ; 

__attribute__((used)) static int adsp_probe(struct platform_device *pdev)
{
	const struct adsp_data *desc;
	struct qcom_adsp *adsp;
	struct rproc *rproc;
	int ret;

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		return -EINVAL;

	if (!qcom_scm_is_available())
		return -EPROBE_DEFER;

	rproc = rproc_alloc(&pdev->dev, pdev->name, &adsp_ops,
			    desc->firmware_name, sizeof(*adsp));
	if (!rproc) {
		dev_err(&pdev->dev, "unable to allocate remoteproc\n");
		return -ENOMEM;
	}

	adsp = (struct qcom_adsp *)rproc->priv;
	adsp->dev = &pdev->dev;
	adsp->rproc = rproc;
	adsp->pas_id = desc->pas_id;
	adsp->has_aggre2_clk = desc->has_aggre2_clk;
	platform_set_drvdata(pdev, adsp);

	ret = adsp_alloc_memory_region(adsp);
	if (ret)
		goto free_rproc;

	ret = adsp_init_clock(adsp);
	if (ret)
		goto free_rproc;

	ret = adsp_init_regulator(adsp);
	if (ret)
		goto free_rproc;

	ret = qcom_q6v5_init(&adsp->q6v5, pdev, rproc, desc->crash_reason_smem,
			     qcom_pas_handover);
	if (ret)
		goto free_rproc;

	qcom_add_glink_subdev(rproc, &adsp->glink_subdev);
	qcom_add_smd_subdev(rproc, &adsp->smd_subdev);
	qcom_add_ssr_subdev(rproc, &adsp->ssr_subdev, desc->ssr_name);
	adsp->sysmon = qcom_add_sysmon_subdev(rproc,
					      desc->sysmon_name,
					      desc->ssctl_id);

	ret = rproc_add(rproc);
	if (ret)
		goto free_rproc;

	return 0;

free_rproc:
	rproc_free(rproc);

	return ret;
}