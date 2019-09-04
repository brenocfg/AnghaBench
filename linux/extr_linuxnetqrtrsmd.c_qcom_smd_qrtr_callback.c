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
typedef  int /*<<< orphan*/  u32 ;
struct rpmsg_device {int /*<<< orphan*/  dev; } ;
struct qrtr_smd_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ep; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct qrtr_smd_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int qrtr_endpoint_post (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static int qcom_smd_qrtr_callback(struct rpmsg_device *rpdev,
				  void *data, int len, void *priv, u32 addr)
{
	struct qrtr_smd_dev *qdev = dev_get_drvdata(&rpdev->dev);
	int rc;

	if (!qdev)
		return -EAGAIN;

	rc = qrtr_endpoint_post(&qdev->ep, data, len);
	if (rc == -EINVAL) {
		dev_err(qdev->dev, "invalid ipcrouter packet\n");
		/* return 0 to let smd drop the packet */
		rc = 0;
	}

	return rc;
}