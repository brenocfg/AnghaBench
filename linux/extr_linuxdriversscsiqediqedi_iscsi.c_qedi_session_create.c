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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u16 ;
struct qedi_endpoint {TYPE_1__* qedi; } ;
struct qedi_ctx {scalar_t__ max_sqes; int /*<<< orphan*/  dbg_ctx; } ;
struct qedi_cmd {int dummy; } ;
struct iscsi_endpoint {struct qedi_endpoint* dd_data; } ;
struct iscsi_cls_session {int /*<<< orphan*/  dd_data; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {struct Scsi_Host* shost; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_MAX_TARGET ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*,struct qedi_endpoint*) ; 
 scalar_t__ QEDI_SQ_WQES_MIN ; 
 struct qedi_ctx* iscsi_host_priv (struct Scsi_Host*) ; 
 struct iscsi_cls_session* iscsi_session_setup (int /*<<< orphan*/ *,struct Scsi_Host*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_session_teardown (struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  qedi_iscsi_transport ; 
 scalar_t__ qedi_setup_cmd_pool (struct qedi_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iscsi_cls_session *
qedi_session_create(struct iscsi_endpoint *ep, u16 cmds_max,
		    u16 qdepth, uint32_t initial_cmdsn)
{
	struct Scsi_Host *shost;
	struct iscsi_cls_session *cls_session;
	struct qedi_ctx *qedi;
	struct qedi_endpoint *qedi_ep;

	if (!ep)
		return NULL;

	qedi_ep = ep->dd_data;
	shost = qedi_ep->qedi->shost;
	qedi = iscsi_host_priv(shost);

	if (cmds_max > qedi->max_sqes)
		cmds_max = qedi->max_sqes;
	else if (cmds_max < QEDI_SQ_WQES_MIN)
		cmds_max = QEDI_SQ_WQES_MIN;

	cls_session = iscsi_session_setup(&qedi_iscsi_transport, shost,
					  cmds_max, 0, sizeof(struct qedi_cmd),
					  initial_cmdsn, ISCSI_MAX_TARGET);
	if (!cls_session) {
		QEDI_ERR(&qedi->dbg_ctx,
			 "Failed to setup session for ep=%p\n", qedi_ep);
		return NULL;
	}

	if (qedi_setup_cmd_pool(qedi, cls_session->dd_data)) {
		QEDI_ERR(&qedi->dbg_ctx,
			 "Failed to setup cmd pool for ep=%p\n", qedi_ep);
		goto session_teardown;
	}

	return cls_session;

session_teardown:
	iscsi_session_teardown(cls_session);
	return NULL;
}