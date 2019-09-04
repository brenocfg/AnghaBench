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
struct qedf_ctx {scalar_t__ vlan_id; int /*<<< orphan*/  ctlr; int /*<<< orphan*/  fipvlan_compl; int /*<<< orphan*/  fipvlan_retries; int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  link_state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ QEDF_LINK_UP ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcoe_ctlr_link_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedf_fcoe_send_vlan_req (struct qedf_ctx*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool qedf_initiate_fipvlan_req(struct qedf_ctx *qedf)
{
	int rc;

	if (atomic_read(&qedf->link_state) != QEDF_LINK_UP) {
		QEDF_ERR(&(qedf->dbg_ctx), "Link not up.\n");
		return  false;
	}

	while (qedf->fipvlan_retries--) {
		if (qedf->vlan_id > 0)
			return true;
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			   "Retry %d.\n", qedf->fipvlan_retries);
		init_completion(&qedf->fipvlan_compl);
		qedf_fcoe_send_vlan_req(qedf);
		rc = wait_for_completion_timeout(&qedf->fipvlan_compl,
		    1 * HZ);
		if (rc > 0) {
			fcoe_ctlr_link_up(&qedf->ctlr);
			return true;
		}
	}

	return false;
}