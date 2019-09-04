#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct zfcp_fsf_ct_els {int /*<<< orphan*/ * resp; int /*<<< orphan*/ * req; int /*<<< orphan*/ * handler_data; int /*<<< orphan*/  handler; } ;
struct TYPE_8__ {int /*<<< orphan*/  fp_fid; } ;
struct TYPE_9__ {int fr_name_len; int /*<<< orphan*/  fr_name; TYPE_3__ fr_fid; } ;
struct zfcp_fc_rspn_req {TYPE_4__ rspn; int /*<<< orphan*/  ct_hdr; } ;
struct TYPE_6__ {struct zfcp_fc_rspn_req rsp; struct zfcp_fc_rspn_req req; } ;
struct TYPE_7__ {TYPE_1__ rspn; } ;
struct zfcp_fc_req {int /*<<< orphan*/  sg_rsp; int /*<<< orphan*/  sg_req; TYPE_2__ u; struct zfcp_fsf_ct_els ct_els; } ;
struct zfcp_adapter {TYPE_5__* gs; struct Scsi_Host* scsi_host; } ;
struct fc_ct_hdr {TYPE_4__ rspn; int /*<<< orphan*/  ct_hdr; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_NS_RSPN_ID ; 
 int /*<<< orphan*/  FC_SYMBOLIC_NAME_SIZE ; 
 int /*<<< orphan*/  ZFCP_FC_CTELS_TMO ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  fc_host_port_id (struct Scsi_Host*) ; 
 int /*<<< orphan*/  fc_host_symbolic_name (struct Scsi_Host*) ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,struct zfcp_fc_rspn_req*,int) ; 
 int strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fc_complete ; 
 int /*<<< orphan*/  zfcp_fc_ct_ns_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfcp_fsf_send_ct (int /*<<< orphan*/ *,struct zfcp_fsf_ct_els*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_fc_rspn(struct zfcp_adapter *adapter,
			 struct zfcp_fc_req *fc_req)
{
	DECLARE_COMPLETION_ONSTACK(completion);
	struct Scsi_Host *shost = adapter->scsi_host;
	struct zfcp_fsf_ct_els *ct_els = &fc_req->ct_els;
	struct zfcp_fc_rspn_req *rspn_req = &fc_req->u.rspn.req;
	struct fc_ct_hdr *rspn_rsp = &fc_req->u.rspn.rsp;
	int ret, len;

	zfcp_fc_ct_ns_init(&rspn_req->ct_hdr, FC_NS_RSPN_ID,
			   FC_SYMBOLIC_NAME_SIZE);
	hton24(rspn_req->rspn.fr_fid.fp_fid, fc_host_port_id(shost));
	len = strlcpy(rspn_req->rspn.fr_name, fc_host_symbolic_name(shost),
		      FC_SYMBOLIC_NAME_SIZE);
	rspn_req->rspn.fr_name_len = len;

	sg_init_one(&fc_req->sg_req, rspn_req, sizeof(*rspn_req));
	sg_init_one(&fc_req->sg_rsp, rspn_rsp, sizeof(*rspn_rsp));

	ct_els->handler = zfcp_fc_complete;
	ct_els->handler_data = &completion;
	ct_els->req = &fc_req->sg_req;
	ct_els->resp = &fc_req->sg_rsp;

	ret = zfcp_fsf_send_ct(&adapter->gs->ds, ct_els, NULL,
			       ZFCP_FC_CTELS_TMO);
	if (!ret)
		wait_for_completion(&completion);
}