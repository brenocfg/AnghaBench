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
struct qedf_ctx {int /*<<< orphan*/  link_update; int /*<<< orphan*/  link_update_wq; scalar_t__ vlan_id; int /*<<< orphan*/  link_state; } ;
struct fc_lport {scalar_t__ vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_LINK_DOWN ; 
 int /*<<< orphan*/  QEDF_LINK_UP ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qedf_ctx* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  qedf_wait_for_upload (struct qedf_ctx*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedf_ctx_soft_reset(struct fc_lport *lport)
{
	struct qedf_ctx *qedf;

	if (lport->vport) {
		QEDF_ERR(NULL, "Cannot issue host reset on NPIV port.\n");
		return;
	}

	qedf = lport_priv(lport);

	/* For host reset, essentially do a soft link up/down */
	atomic_set(&qedf->link_state, QEDF_LINK_DOWN);
	queue_delayed_work(qedf->link_update_wq, &qedf->link_update,
	    0);
	qedf_wait_for_upload(qedf);
	atomic_set(&qedf->link_state, QEDF_LINK_UP);
	qedf->vlan_id  = 0;
	queue_delayed_work(qedf->link_update_wq, &qedf->link_update,
	    0);
}