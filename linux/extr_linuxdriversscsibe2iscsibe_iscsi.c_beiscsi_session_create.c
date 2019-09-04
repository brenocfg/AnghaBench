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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct iscsi_session {struct beiscsi_session* dd_data; } ;
struct iscsi_endpoint {struct beiscsi_endpoint* dd_data; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct beiscsi_session {int /*<<< orphan*/  bhs_pool; } ;
struct beiscsi_io_task {int dummy; } ;
struct TYPE_3__ {scalar_t__ wrbs_per_cxn; } ;
struct beiscsi_hba {TYPE_2__* pcidev; struct Scsi_Host* shost; TYPE_1__ params; int /*<<< orphan*/  state; } ;
struct beiscsi_endpoint {struct beiscsi_hba* phba; } ;
struct be_cmd_bhs {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  ISCSI_MAX_TARGET ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_hba_is_online (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_iscsi_transport ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dma_pool_create (char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct iscsi_cls_session* iscsi_session_setup (int /*<<< orphan*/ *,struct Scsi_Host*,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_session_teardown (struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct iscsi_cls_session *beiscsi_session_create(struct iscsi_endpoint *ep,
						 u16 cmds_max,
						 u16 qdepth,
						 u32 initial_cmdsn)
{
	struct Scsi_Host *shost;
	struct beiscsi_endpoint *beiscsi_ep;
	struct iscsi_cls_session *cls_session;
	struct beiscsi_hba *phba;
	struct iscsi_session *sess;
	struct beiscsi_session *beiscsi_sess;
	struct beiscsi_io_task *io_task;


	if (!ep) {
		pr_err("beiscsi_session_create: invalid ep\n");
		return NULL;
	}
	beiscsi_ep = ep->dd_data;
	phba = beiscsi_ep->phba;

	if (!beiscsi_hba_is_online(phba)) {
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
		return NULL;
	}

	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In beiscsi_session_create\n");
	if (cmds_max > beiscsi_ep->phba->params.wrbs_per_cxn) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Cannot handle %d cmds."
			    "Max cmds per session supported is %d. Using %d."
			    "\n", cmds_max,
			    beiscsi_ep->phba->params.wrbs_per_cxn,
			    beiscsi_ep->phba->params.wrbs_per_cxn);

		cmds_max = beiscsi_ep->phba->params.wrbs_per_cxn;
	}

	shost = phba->shost;
	cls_session = iscsi_session_setup(&beiscsi_iscsi_transport,
					  shost, cmds_max,
					  sizeof(*beiscsi_sess),
					  sizeof(*io_task),
					  initial_cmdsn, ISCSI_MAX_TARGET);
	if (!cls_session)
		return NULL;
	sess = cls_session->dd_data;
	beiscsi_sess = sess->dd_data;
	beiscsi_sess->bhs_pool =  dma_pool_create("beiscsi_bhs_pool",
						   &phba->pcidev->dev,
						   sizeof(struct be_cmd_bhs),
						   64, 0);
	if (!beiscsi_sess->bhs_pool)
		goto destroy_sess;

	return cls_session;
destroy_sess:
	iscsi_session_teardown(cls_session);
	return NULL;
}