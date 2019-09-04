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
struct qcom_wcnss {int /*<<< orphan*/  rproc; int /*<<< orphan*/  smd_subdev; int /*<<< orphan*/  sysmon; int /*<<< orphan*/  state; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 
 struct qcom_wcnss* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  qcom_remove_smd_subdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_remove_sysmon_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smem_state_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wcnss_remove(struct platform_device *pdev)
{
	struct qcom_wcnss *wcnss = platform_get_drvdata(pdev);

	of_platform_depopulate(&pdev->dev);

	qcom_smem_state_put(wcnss->state);
	rproc_del(wcnss->rproc);

	qcom_remove_sysmon_subdev(wcnss->sysmon);
	qcom_remove_smd_subdev(wcnss->rproc, &wcnss->smd_subdev);
	rproc_free(wcnss->rproc);

	return 0;
}