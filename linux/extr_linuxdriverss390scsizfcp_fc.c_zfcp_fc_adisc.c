#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zfcp_port {int /*<<< orphan*/  d_id; struct zfcp_adapter* adapter; } ;
struct TYPE_7__ {struct zfcp_fc_req* handler_data; int /*<<< orphan*/  handler; int /*<<< orphan*/ * resp; int /*<<< orphan*/ * req; struct zfcp_port* port; } ;
struct TYPE_8__ {int /*<<< orphan*/  adisc_port_id; int /*<<< orphan*/  adisc_cmd; void* adisc_wwnn; void* adisc_wwpn; } ;
struct TYPE_5__ {TYPE_4__ req; TYPE_4__ rsp; } ;
struct TYPE_6__ {TYPE_1__ adisc; } ;
struct zfcp_fc_req {TYPE_3__ ct_els; TYPE_2__ u; int /*<<< orphan*/  sg_rsp; int /*<<< orphan*/  sg_req; } ;
struct zfcp_adapter {struct Scsi_Host* scsi_host; } ;
struct fc_els_adisc {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_ADISC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ZFCP_FC_CTELS_TMO ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_host_node_name (struct Scsi_Host*) ; 
 int /*<<< orphan*/  fc_host_port_id (struct Scsi_Host*) ; 
 int /*<<< orphan*/  fc_host_port_name (struct Scsi_Host*) ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct zfcp_fc_req*) ; 
 struct zfcp_fc_req* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  zfcp_fc_adisc_handler ; 
 int /*<<< orphan*/  zfcp_fc_req_cache ; 
 int zfcp_fsf_send_els (struct zfcp_adapter*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_fc_adisc(struct zfcp_port *port)
{
	struct zfcp_fc_req *fc_req;
	struct zfcp_adapter *adapter = port->adapter;
	struct Scsi_Host *shost = adapter->scsi_host;
	int ret;

	fc_req = kmem_cache_zalloc(zfcp_fc_req_cache, GFP_ATOMIC);
	if (!fc_req)
		return -ENOMEM;

	fc_req->ct_els.port = port;
	fc_req->ct_els.req = &fc_req->sg_req;
	fc_req->ct_els.resp = &fc_req->sg_rsp;
	sg_init_one(&fc_req->sg_req, &fc_req->u.adisc.req,
		    sizeof(struct fc_els_adisc));
	sg_init_one(&fc_req->sg_rsp, &fc_req->u.adisc.rsp,
		    sizeof(struct fc_els_adisc));

	fc_req->ct_els.handler = zfcp_fc_adisc_handler;
	fc_req->ct_els.handler_data = fc_req;

	/* acc. to FC-FS, hard_nport_id in ADISC should not be set for ports
	   without FC-AL-2 capability, so we don't set it */
	fc_req->u.adisc.req.adisc_wwpn = cpu_to_be64(fc_host_port_name(shost));
	fc_req->u.adisc.req.adisc_wwnn = cpu_to_be64(fc_host_node_name(shost));
	fc_req->u.adisc.req.adisc_cmd = ELS_ADISC;
	hton24(fc_req->u.adisc.req.adisc_port_id, fc_host_port_id(shost));

	ret = zfcp_fsf_send_els(adapter, port->d_id, &fc_req->ct_els,
				ZFCP_FC_CTELS_TMO);
	if (ret)
		kmem_cache_free(zfcp_fc_req_cache, fc_req);

	return ret;
}