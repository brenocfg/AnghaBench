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
struct rpmsg_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  ept; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct instance_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MSG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct instance_data*) ; 
 struct instance_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int rpmsg_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpmsg_sample_probe(struct rpmsg_device *rpdev)
{
	int ret;
	struct instance_data *idata;

	dev_info(&rpdev->dev, "new channel: 0x%x -> 0x%x!\n",
					rpdev->src, rpdev->dst);

	idata = devm_kzalloc(&rpdev->dev, sizeof(*idata), GFP_KERNEL);
	if (!idata)
		return -ENOMEM;

	dev_set_drvdata(&rpdev->dev, idata);

	/* send a message to our remote processor */
	ret = rpmsg_send(rpdev->ept, MSG, strlen(MSG));
	if (ret) {
		dev_err(&rpdev->dev, "rpmsg_send failed: %d\n", ret);
		return ret;
	}

	return 0;
}