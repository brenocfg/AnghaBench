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
struct qcom_slim_ngd_ctrl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int qcom_slim_ngd_init_rx_msgq (struct qcom_slim_ngd_ctrl*) ; 
 int qcom_slim_ngd_init_tx_msgq (struct qcom_slim_ngd_ctrl*) ; 

__attribute__((used)) static int qcom_slim_ngd_init_dma(struct qcom_slim_ngd_ctrl *ctrl)
{
	int ret = 0;

	ret = qcom_slim_ngd_init_rx_msgq(ctrl);
	if (ret) {
		dev_err(ctrl->dev, "rx dma init failed\n");
		return ret;
	}

	ret = qcom_slim_ngd_init_tx_msgq(ctrl);
	if (ret)
		dev_err(ctrl->dev, "tx dma init failed\n");

	return ret;
}