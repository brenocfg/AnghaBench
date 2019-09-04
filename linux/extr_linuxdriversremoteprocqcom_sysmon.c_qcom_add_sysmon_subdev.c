#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct rproc {TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_5__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  start; } ;
struct qcom_sysmon {char const* name; int ssctl_instance; int /*<<< orphan*/  node; TYPE_3__ nb; TYPE_2__ subdev; int /*<<< orphan*/  qmi; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  comp; struct rproc* rproc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SSCTL_MAX_MSG_LEN ; 
 int /*<<< orphan*/  blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qcom_sysmon*) ; 
 struct qcom_sysmon* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qmi_add_lookup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qmi_handle_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rproc_add_subdev (struct rproc*,TYPE_2__*) ; 
 int /*<<< orphan*/  ssctl_ops ; 
 int /*<<< orphan*/  sysmon_list ; 
 int /*<<< orphan*/  sysmon_lock ; 
 int /*<<< orphan*/  sysmon_notifiers ; 
 int /*<<< orphan*/  sysmon_notify ; 
 int /*<<< orphan*/  sysmon_start ; 
 int /*<<< orphan*/  sysmon_stop ; 

struct qcom_sysmon *qcom_add_sysmon_subdev(struct rproc *rproc,
					   const char *name,
					   int ssctl_instance)
{
	struct qcom_sysmon *sysmon;
	int ret;

	sysmon = kzalloc(sizeof(*sysmon), GFP_KERNEL);
	if (!sysmon)
		return NULL;

	sysmon->dev = rproc->dev.parent;
	sysmon->rproc = rproc;

	sysmon->name = name;
	sysmon->ssctl_instance = ssctl_instance;

	init_completion(&sysmon->comp);
	mutex_init(&sysmon->lock);

	ret = qmi_handle_init(&sysmon->qmi, SSCTL_MAX_MSG_LEN, &ssctl_ops, NULL);
	if (ret < 0) {
		dev_err(sysmon->dev, "failed to initialize qmi handle\n");
		kfree(sysmon);
		return NULL;
	}

	qmi_add_lookup(&sysmon->qmi, 43, 0, 0);

	sysmon->subdev.start = sysmon_start;
	sysmon->subdev.stop = sysmon_stop;

	rproc_add_subdev(rproc, &sysmon->subdev);

	sysmon->nb.notifier_call = sysmon_notify;
	blocking_notifier_chain_register(&sysmon_notifiers, &sysmon->nb);

	mutex_lock(&sysmon_lock);
	list_add(&sysmon->node, &sysmon_list);
	mutex_unlock(&sysmon_lock);

	return sysmon;
}