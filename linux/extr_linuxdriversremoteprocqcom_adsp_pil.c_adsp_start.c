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
struct qcom_adsp {int /*<<< orphan*/  xo; int /*<<< orphan*/  aggre2_clk; int /*<<< orphan*/  cx_supply; int /*<<< orphan*/  px_supply; int /*<<< orphan*/  pas_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  q6v5; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  qcom_q6v5_prepare (int /*<<< orphan*/ *) ; 
 int qcom_q6v5_wait_for_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qcom_scm_pas_auth_and_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_scm_pas_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adsp_start(struct rproc *rproc)
{
	struct qcom_adsp *adsp = (struct qcom_adsp *)rproc->priv;
	int ret;

	qcom_q6v5_prepare(&adsp->q6v5);

	ret = clk_prepare_enable(adsp->xo);
	if (ret)
		return ret;

	ret = clk_prepare_enable(adsp->aggre2_clk);
	if (ret)
		goto disable_xo_clk;

	ret = regulator_enable(adsp->cx_supply);
	if (ret)
		goto disable_aggre2_clk;

	ret = regulator_enable(adsp->px_supply);
	if (ret)
		goto disable_cx_supply;

	ret = qcom_scm_pas_auth_and_reset(adsp->pas_id);
	if (ret) {
		dev_err(adsp->dev,
			"failed to authenticate image and release reset\n");
		goto disable_px_supply;
	}

	ret = qcom_q6v5_wait_for_start(&adsp->q6v5, msecs_to_jiffies(5000));
	if (ret == -ETIMEDOUT) {
		dev_err(adsp->dev, "start timed out\n");
		qcom_scm_pas_shutdown(adsp->pas_id);
		goto disable_px_supply;
	}

	return 0;

disable_px_supply:
	regulator_disable(adsp->px_supply);
disable_cx_supply:
	regulator_disable(adsp->cx_supply);
disable_aggre2_clk:
	clk_disable_unprepare(adsp->aggre2_clk);
disable_xo_clk:
	clk_disable_unprepare(adsp->xo);

	return ret;
}