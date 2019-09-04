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
struct zfcp_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  d_id; } ;
struct zfcp_fsf_ct_els {int /*<<< orphan*/  handler; } ;
struct zfcp_adapter {int dummy; } ;
struct fc_rport {int /*<<< orphan*/  port_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_4__ {TYPE_1__ h_els; } ;
struct fc_bsg_request {TYPE_2__ rqst_data; } ;
struct bsg_job {int timeout; struct fc_bsg_request* request; struct zfcp_fsf_ct_els* dd_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 struct fc_rport* fc_bsg_to_rport (struct bsg_job*) ; 
 int /*<<< orphan*/  ntoh24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fc_ct_els_job_handler ; 
 int zfcp_fsf_send_els (struct zfcp_adapter*,int /*<<< orphan*/ ,struct zfcp_fsf_ct_els*,int) ; 
 struct zfcp_port* zfcp_get_port_by_wwpn (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_fc_exec_els_job(struct bsg_job *job,
				struct zfcp_adapter *adapter)
{
	struct zfcp_fsf_ct_els *els = job->dd_data;
	struct fc_rport *rport = fc_bsg_to_rport(job);
	struct fc_bsg_request *bsg_request = job->request;
	struct zfcp_port *port;
	u32 d_id;

	if (rport) {
		port = zfcp_get_port_by_wwpn(adapter, rport->port_name);
		if (!port)
			return -EINVAL;

		d_id = port->d_id;
		put_device(&port->dev);
	} else
		d_id = ntoh24(bsg_request->rqst_data.h_els.port_id);

	els->handler = zfcp_fc_ct_els_job_handler;
	return zfcp_fsf_send_els(adapter, d_id, els, job->timeout / HZ);
}