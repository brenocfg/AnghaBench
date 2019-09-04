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
struct qcom_wcnss {scalar_t__ ready_irq; int /*<<< orphan*/  iris_lock; int /*<<< orphan*/  vregs; int /*<<< orphan*/  num_vregs; int /*<<< orphan*/  iris; int /*<<< orphan*/  dev; int /*<<< orphan*/  start_done; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WCNSS_PAS_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_iris_disable (int /*<<< orphan*/ ) ; 
 int qcom_iris_enable (int /*<<< orphan*/ ) ; 
 int qcom_scm_pas_auth_and_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_scm_pas_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcnss_configure_iris (struct qcom_wcnss*) ; 
 int /*<<< orphan*/  wcnss_indicate_nv_download (struct qcom_wcnss*) ; 

__attribute__((used)) static int wcnss_start(struct rproc *rproc)
{
	struct qcom_wcnss *wcnss = (struct qcom_wcnss *)rproc->priv;
	int ret;

	mutex_lock(&wcnss->iris_lock);
	if (!wcnss->iris) {
		dev_err(wcnss->dev, "no iris registered\n");
		ret = -EINVAL;
		goto release_iris_lock;
	}

	ret = regulator_bulk_enable(wcnss->num_vregs, wcnss->vregs);
	if (ret)
		goto release_iris_lock;

	ret = qcom_iris_enable(wcnss->iris);
	if (ret)
		goto disable_regulators;

	wcnss_indicate_nv_download(wcnss);
	wcnss_configure_iris(wcnss);

	ret = qcom_scm_pas_auth_and_reset(WCNSS_PAS_ID);
	if (ret) {
		dev_err(wcnss->dev,
			"failed to authenticate image and release reset\n");
		goto disable_iris;
	}

	ret = wait_for_completion_timeout(&wcnss->start_done,
					  msecs_to_jiffies(5000));
	if (wcnss->ready_irq > 0 && ret == 0) {
		/* We have a ready_irq, but it didn't fire in time. */
		dev_err(wcnss->dev, "start timed out\n");
		qcom_scm_pas_shutdown(WCNSS_PAS_ID);
		ret = -ETIMEDOUT;
		goto disable_iris;
	}

	ret = 0;

disable_iris:
	qcom_iris_disable(wcnss->iris);
disable_regulators:
	regulator_bulk_disable(wcnss->num_vregs, wcnss->vregs);
release_iris_lock:
	mutex_unlock(&wcnss->iris_lock);

	return ret;
}