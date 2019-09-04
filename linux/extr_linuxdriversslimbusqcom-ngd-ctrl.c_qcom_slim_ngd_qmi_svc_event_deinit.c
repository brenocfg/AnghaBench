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
struct qcom_slim_ngd_qmi {int /*<<< orphan*/  svc_event_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  qmi_handle_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qcom_slim_ngd_qmi_svc_event_deinit(struct qcom_slim_ngd_qmi *qmi)
{
	qmi_handle_release(&qmi->svc_event_hdl);
}