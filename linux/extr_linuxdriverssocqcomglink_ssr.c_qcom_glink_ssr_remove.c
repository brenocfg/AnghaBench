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
struct rpmsg_device {int /*<<< orphan*/  dev; } ;
struct glink_ssr {int /*<<< orphan*/  nb; } ;

/* Variables and functions */
 struct glink_ssr* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_unregister_ssr_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qcom_glink_ssr_remove(struct rpmsg_device *rpdev)
{
	struct glink_ssr *ssr = dev_get_drvdata(&rpdev->dev);

	qcom_unregister_ssr_notifier(&ssr->nb);
}