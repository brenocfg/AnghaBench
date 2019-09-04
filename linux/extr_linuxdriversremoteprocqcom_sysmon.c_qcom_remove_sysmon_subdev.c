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
struct qcom_sysmon {int /*<<< orphan*/  qmi; int /*<<< orphan*/  subdev; int /*<<< orphan*/  rproc; int /*<<< orphan*/  nb; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qcom_sysmon*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmi_handle_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rproc_remove_subdev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysmon_lock ; 
 int /*<<< orphan*/  sysmon_notifiers ; 

void qcom_remove_sysmon_subdev(struct qcom_sysmon *sysmon)
{
	if (!sysmon)
		return;

	mutex_lock(&sysmon_lock);
	list_del(&sysmon->node);
	mutex_unlock(&sysmon_lock);

	blocking_notifier_chain_unregister(&sysmon_notifiers, &sysmon->nb);

	rproc_remove_subdev(sysmon->rproc, &sysmon->subdev);

	qmi_handle_release(&sysmon->qmi);

	kfree(sysmon);
}