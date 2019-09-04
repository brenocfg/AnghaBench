#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpmsg_device {TYPE_1__* ept; } ;
struct qcom_sysmon {int /*<<< orphan*/ * ept; } ;
struct TYPE_2__ {struct qcom_sysmon* priv; } ;

/* Variables and functions */

__attribute__((used)) static void sysmon_remove(struct rpmsg_device *rpdev)
{
	struct qcom_sysmon *sysmon = rpdev->ept->priv;

	sysmon->ept = NULL;
}