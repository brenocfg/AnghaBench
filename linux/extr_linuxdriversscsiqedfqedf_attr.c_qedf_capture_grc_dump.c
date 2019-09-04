#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qedf_ctx {TYPE_1__* lport; int /*<<< orphan*/  flags; int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  grcdump_size; int /*<<< orphan*/  grcdump; int /*<<< orphan*/  cdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  common; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_GRCDUMP_CAPTURE ; 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  QEDF_LOG_INFO ; 
 int /*<<< orphan*/  QEDF_UEVENT_CODE_GRCDUMP ; 
 TYPE_2__* qed_ops ; 
 struct qedf_ctx* qedf_get_base_qedf (struct qedf_ctx*) ; 
 int /*<<< orphan*/  qedf_get_grc_dump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ qedf_is_vport (struct qedf_ctx*) ; 
 int /*<<< orphan*/  qedf_uevent_emit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qedf_capture_grc_dump(struct qedf_ctx *qedf)
{
	struct qedf_ctx *base_qedf;

	/* Make sure we use the base qedf to take the GRC dump */
	if (qedf_is_vport(qedf))
		base_qedf = qedf_get_base_qedf(qedf);
	else
		base_qedf = qedf;

	if (test_bit(QEDF_GRCDUMP_CAPTURE, &base_qedf->flags)) {
		QEDF_INFO(&(base_qedf->dbg_ctx), QEDF_LOG_INFO,
		    "GRC Dump already captured.\n");
		return;
	}


	qedf_get_grc_dump(base_qedf->cdev, qed_ops->common,
	    &base_qedf->grcdump, &base_qedf->grcdump_size);
	QEDF_ERR(&(base_qedf->dbg_ctx), "GRC Dump captured.\n");
	set_bit(QEDF_GRCDUMP_CAPTURE, &base_qedf->flags);
	qedf_uevent_emit(base_qedf->lport->host, QEDF_UEVENT_CODE_GRCDUMP,
	    NULL);
}