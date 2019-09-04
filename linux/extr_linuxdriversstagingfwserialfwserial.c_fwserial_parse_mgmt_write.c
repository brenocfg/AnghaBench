#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fwtty_port {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  plug_req; } ;
struct fwtty_peer {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  unit; int /*<<< orphan*/  work; int /*<<< orphan*/  workfn; struct fwtty_port* port; TYPE_1__ work_params; } ;
struct TYPE_5__ {int /*<<< orphan*/  code; int /*<<< orphan*/  len; } ;
struct fwserial_mgmt_pkt {TYPE_2__ hdr; int /*<<< orphan*/  plug_rsp; int /*<<< orphan*/  plug_req; } ;
struct TYPE_6__ {unsigned long long offset; } ;

/* Variables and functions */
 scalar_t__ FWPS_GONE ; 
 scalar_t__ FWPS_PLUG_PENDING ; 
 scalar_t__ FWPS_UNPLUG_PENDING ; 
 int FWSC_CODE_MASK ; 
 int FWSC_RSP_NACK ; 
#define  FWSC_VIRT_CABLE_PLUG 131 
#define  FWSC_VIRT_CABLE_PLUG_RSP 130 
#define  FWSC_VIRT_CABLE_UNPLUG 129 
#define  FWSC_VIRT_CABLE_UNPLUG_RSP 128 
 int RCODE_ADDRESS_ERROR ; 
 int RCODE_COMPLETE ; 
 int RCODE_CONFLICT_ERROR ; 
 int RCODE_DATA_ERROR ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwserial_handle_plug_req ; 
 int /*<<< orphan*/  fwserial_handle_unplug_req ; 
 TYPE_3__ fwserial_mgmt_addr_handler ; 
 int /*<<< orphan*/  fwserial_release_port (struct fwtty_port*,int) ; 
 int /*<<< orphan*/  fwserial_virt_plug_complete (struct fwtty_peer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwtty_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwtty_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fwtty_notice (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fwtty_write_port_status (struct fwtty_port*) ; 
 size_t mgmt_pkt_expected_len (int /*<<< orphan*/ ) ; 
 struct fwtty_port* peer_revert_state (struct fwtty_peer*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_unbound_wq ; 
 int /*<<< orphan*/  work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fwserial_parse_mgmt_write(struct fwtty_peer *peer,
				     struct fwserial_mgmt_pkt *pkt,
				     unsigned long long addr,
				     size_t len)
{
	struct fwtty_port *port = NULL;
	bool reset = false;
	int rcode;

	if (addr != fwserial_mgmt_addr_handler.offset || len < sizeof(pkt->hdr))
		return RCODE_ADDRESS_ERROR;

	if (len != be16_to_cpu(pkt->hdr.len) ||
	    len != mgmt_pkt_expected_len(pkt->hdr.code))
		return RCODE_DATA_ERROR;

	spin_lock_bh(&peer->lock);
	if (peer->state == FWPS_GONE) {
		/*
		 * This should never happen - it would mean that the
		 * remote unit that just wrote this transaction was
		 * already removed from the bus -- and the removal was
		 * processed before we rec'd this transaction
		 */
		fwtty_err(&peer->unit, "peer already removed\n");
		spin_unlock_bh(&peer->lock);
		return RCODE_ADDRESS_ERROR;
	}

	rcode = RCODE_COMPLETE;

	fwtty_dbg(&peer->unit, "mgmt: hdr.code: %04hx\n", pkt->hdr.code);

	switch (be16_to_cpu(pkt->hdr.code) & FWSC_CODE_MASK) {
	case FWSC_VIRT_CABLE_PLUG:
		if (work_pending(&peer->work)) {
			fwtty_err(&peer->unit, "plug req: busy\n");
			rcode = RCODE_CONFLICT_ERROR;

		} else {
			peer->work_params.plug_req = pkt->plug_req;
			peer->workfn = fwserial_handle_plug_req;
			queue_work(system_unbound_wq, &peer->work);
		}
		break;

	case FWSC_VIRT_CABLE_PLUG_RSP:
		if (peer->state != FWPS_PLUG_PENDING) {
			rcode = RCODE_CONFLICT_ERROR;

		} else if (be16_to_cpu(pkt->hdr.code) & FWSC_RSP_NACK) {
			fwtty_notice(&peer->unit, "NACK plug rsp\n");
			port = peer_revert_state(peer);

		} else {
			struct fwtty_port *tmp = peer->port;

			fwserial_virt_plug_complete(peer, &pkt->plug_rsp);
			spin_unlock_bh(&peer->lock);

			fwtty_write_port_status(tmp);
			spin_lock_bh(&peer->lock);
		}
		break;

	case FWSC_VIRT_CABLE_UNPLUG:
		if (work_pending(&peer->work)) {
			fwtty_err(&peer->unit, "unplug req: busy\n");
			rcode = RCODE_CONFLICT_ERROR;
		} else {
			peer->workfn = fwserial_handle_unplug_req;
			queue_work(system_unbound_wq, &peer->work);
		}
		break;

	case FWSC_VIRT_CABLE_UNPLUG_RSP:
		if (peer->state != FWPS_UNPLUG_PENDING) {
			rcode = RCODE_CONFLICT_ERROR;
		} else {
			if (be16_to_cpu(pkt->hdr.code) & FWSC_RSP_NACK)
				fwtty_notice(&peer->unit, "NACK unplug?\n");
			port = peer_revert_state(peer);
			reset = true;
		}
		break;

	default:
		fwtty_err(&peer->unit, "unknown mgmt code %d\n",
			  be16_to_cpu(pkt->hdr.code));
		rcode = RCODE_DATA_ERROR;
	}
	spin_unlock_bh(&peer->lock);

	if (port)
		fwserial_release_port(port, reset);

	return rcode;
}