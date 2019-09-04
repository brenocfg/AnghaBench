#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct zfcp_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  status; int /*<<< orphan*/  handle; scalar_t__ wwpn; } ;
struct zfcp_fsf_req {int status; TYPE_6__* qtcb; TYPE_2__* adapter; struct zfcp_port* data; } ;
struct TYPE_9__ {int /*<<< orphan*/ * word; } ;
struct fsf_qtcb_header {int fsf_status; int /*<<< orphan*/  port_handle; TYPE_3__ fsf_status_qual; } ;
struct fc_els_flogi {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  els1_length; scalar_t__ els; } ;
struct TYPE_11__ {TYPE_4__ support; } ;
struct TYPE_12__ {TYPE_5__ bottom; struct fsf_qtcb_header header; } ;
struct TYPE_8__ {TYPE_1__* ccw_device; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  FSF_ADAPTER_STATUS_AVAILABLE 135 
#define  FSF_GOOD 134 
#define  FSF_MAXIMUM_NUMBER_OF_PORTS_EXCEEDED 133 
 int /*<<< orphan*/  FSF_PLOGI_MIN_LEN ; 
#define  FSF_PORT_ALREADY_OPEN 132 
#define  FSF_SQ_INVOKE_LINK_TEST_PROCEDURE 131 
#define  FSF_SQ_NO_RETRY_POSSIBLE 130 
#define  FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED 129 
#define  FSF_UNKNOWN_OP_SUBTYPE 128 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ACCESS_BOXED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_FAILED ; 
 int ZFCP_STATUS_COMMON_OPEN ; 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 int ZFCP_STATUS_PORT_PHYS_OPEN ; 
 int /*<<< orphan*/  atomic_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_or (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_set_port_status (struct zfcp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fc_plogi_evaluate (struct zfcp_port*,struct fc_els_flogi*) ; 

__attribute__((used)) static void zfcp_fsf_open_port_handler(struct zfcp_fsf_req *req)
{
	struct zfcp_port *port = req->data;
	struct fsf_qtcb_header *header = &req->qtcb->header;
	struct fc_els_flogi *plogi;

	if (req->status & ZFCP_STATUS_FSFREQ_ERROR)
		goto out;

	switch (header->fsf_status) {
	case FSF_PORT_ALREADY_OPEN:
		break;
	case FSF_MAXIMUM_NUMBER_OF_PORTS_EXCEEDED:
		dev_warn(&req->adapter->ccw_device->dev,
			 "Not enough FCP adapter resources to open "
			 "remote port 0x%016Lx\n",
			 (unsigned long long)port->wwpn);
		zfcp_erp_set_port_status(port,
					 ZFCP_STATUS_COMMON_ERP_FAILED);
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	case FSF_ADAPTER_STATUS_AVAILABLE:
		switch (header->fsf_status_qual.word[0]) {
		case FSF_SQ_INVOKE_LINK_TEST_PROCEDURE:
			/* no zfcp_fc_test_link() with failed open port */
			/* fall through */
		case FSF_SQ_ULP_DEPENDENT_ERP_REQUIRED:
		case FSF_SQ_NO_RETRY_POSSIBLE:
			req->status |= ZFCP_STATUS_FSFREQ_ERROR;
			break;
		}
		break;
	case FSF_GOOD:
		port->handle = header->port_handle;
		atomic_or(ZFCP_STATUS_COMMON_OPEN |
				ZFCP_STATUS_PORT_PHYS_OPEN, &port->status);
		atomic_andnot(ZFCP_STATUS_COMMON_ACCESS_BOXED,
		                  &port->status);
		/* check whether D_ID has changed during open */
		/*
		 * FIXME: This check is not airtight, as the FCP channel does
		 * not monitor closures of target port connections caused on
		 * the remote side. Thus, they might miss out on invalidating
		 * locally cached WWPNs (and other N_Port parameters) of gone
		 * target ports. So, our heroic attempt to make things safe
		 * could be undermined by 'open port' response data tagged with
		 * obsolete WWPNs. Another reason to monitor potential
		 * connection closures ourself at least (by interpreting
		 * incoming ELS' and unsolicited status). It just crosses my
		 * mind that one should be able to cross-check by means of
		 * another GID_PN straight after a port has been opened.
		 * Alternately, an ADISC/PDISC ELS should suffice, as well.
		 */
		plogi = (struct fc_els_flogi *) req->qtcb->bottom.support.els;
		if (req->qtcb->bottom.support.els1_length >=
		    FSF_PLOGI_MIN_LEN)
				zfcp_fc_plogi_evaluate(port, plogi);
		break;
	case FSF_UNKNOWN_OP_SUBTYPE:
		req->status |= ZFCP_STATUS_FSFREQ_ERROR;
		break;
	}

out:
	put_device(&port->dev);
}