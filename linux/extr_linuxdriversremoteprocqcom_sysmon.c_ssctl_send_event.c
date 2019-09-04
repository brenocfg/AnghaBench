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
struct TYPE_2__ {scalar_t__ result; } ;
struct ssctl_subsys_event_resp {int evt_driven_valid; TYPE_1__ resp; int /*<<< orphan*/  evt_driven; int /*<<< orphan*/  event; int /*<<< orphan*/  subsys_name; int /*<<< orphan*/  subsys_name_len; } ;
struct ssctl_subsys_event_req {int evt_driven_valid; TYPE_1__ resp; int /*<<< orphan*/  evt_driven; int /*<<< orphan*/  event; int /*<<< orphan*/  subsys_name; int /*<<< orphan*/  subsys_name_len; } ;
struct qmi_txn {int dummy; } ;
struct qcom_sysmon {int /*<<< orphan*/  dev; int /*<<< orphan*/  ssctl; int /*<<< orphan*/  qmi; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  SSCTL_SSR_EVENT_BEFORE_SHUTDOWN ; 
 int /*<<< orphan*/  SSCTL_SSR_EVENT_FORCED ; 
 int /*<<< orphan*/  SSCTL_SUBSYS_EVENT_REQ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct ssctl_subsys_event_resp*,int /*<<< orphan*/ ,int) ; 
 int qmi_send_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ssctl_subsys_event_resp*) ; 
 int /*<<< orphan*/  qmi_txn_cancel (struct qmi_txn*) ; 
 int qmi_txn_init (int /*<<< orphan*/ *,struct qmi_txn*,int /*<<< orphan*/ ,struct ssctl_subsys_event_resp*) ; 
 int qmi_txn_wait (struct qmi_txn*,int) ; 
 int /*<<< orphan*/  ssctl_subsys_event_req_ei ; 
 int /*<<< orphan*/  ssctl_subsys_event_resp_ei ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssctl_send_event(struct qcom_sysmon *sysmon, const char *name)
{
	struct ssctl_subsys_event_resp resp;
	struct ssctl_subsys_event_req req;
	struct qmi_txn txn;
	int ret;

	memset(&resp, 0, sizeof(resp));
	ret = qmi_txn_init(&sysmon->qmi, &txn, ssctl_subsys_event_resp_ei, &resp);
	if (ret < 0) {
		dev_err(sysmon->dev, "failed to allocate QMI txn\n");
		return;
	}

	memset(&req, 0, sizeof(req));
	strlcpy(req.subsys_name, name, sizeof(req.subsys_name));
	req.subsys_name_len = strlen(req.subsys_name);
	req.event = SSCTL_SSR_EVENT_BEFORE_SHUTDOWN;
	req.evt_driven_valid = true;
	req.evt_driven = SSCTL_SSR_EVENT_FORCED;

	ret = qmi_send_request(&sysmon->qmi, &sysmon->ssctl, &txn,
			       SSCTL_SUBSYS_EVENT_REQ, 40,
			       ssctl_subsys_event_req_ei, &req);
	if (ret < 0) {
		dev_err(sysmon->dev, "failed to send shutdown request\n");
		qmi_txn_cancel(&txn);
		return;
	}

	ret = qmi_txn_wait(&txn, 5 * HZ);
	if (ret < 0)
		dev_err(sysmon->dev, "failed receiving QMI response\n");
	else if (resp.resp.result)
		dev_err(sysmon->dev, "ssr event send failed\n");
	else
		dev_dbg(sysmon->dev, "ssr event send completed\n");
}