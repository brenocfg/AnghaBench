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
struct work_struct {int dummy; } ;
struct virt_plug_params {int dummy; } ;
struct fwtty_port {int dummy; } ;
struct TYPE_4__ {struct virt_plug_params plug_req; } ;
struct fwtty_peer {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  unit; struct fwtty_port* port; int /*<<< orphan*/  timer; int /*<<< orphan*/  guid; TYPE_3__* serial; TYPE_1__ work_params; } ;
struct fwserial_mgmt_pkt {int dummy; } ;
struct TYPE_6__ {TYPE_2__* card; } ;
struct TYPE_5__ {int /*<<< orphan*/  guid; } ;

/* Variables and functions */
#define  FWPS_NOT_ATTACHED 129 
#define  FWPS_PLUG_PENDING 128 
 int FWPS_PLUG_RESPONDING ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_plug_rsp_nack (struct fwserial_mgmt_pkt*) ; 
 int /*<<< orphan*/  fill_plug_rsp_ok (struct fwserial_mgmt_pkt*,struct fwtty_port*) ; 
 struct fwtty_port* fwserial_find_port (struct fwtty_peer*) ; 
 int /*<<< orphan*/  fwserial_release_port (struct fwtty_port*,int) ; 
 int fwserial_send_mgmt_sync (struct fwtty_peer*,struct fwserial_mgmt_pkt*) ; 
 int /*<<< orphan*/  fwserial_virt_plug_complete (struct fwtty_peer*,struct virt_plug_params*) ; 
 int /*<<< orphan*/  fwtty_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fwtty_write_port_status (struct fwtty_port*) ; 
 int /*<<< orphan*/  kfree (struct fwserial_mgmt_pkt*) ; 
 struct fwserial_mgmt_pkt* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct fwtty_port* peer_revert_state (struct fwtty_peer*) ; 
 int /*<<< orphan*/  peer_set_state (struct fwtty_peer*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct fwtty_peer* to_peer (struct work_struct*,struct work_struct*) ; 

__attribute__((used)) static void fwserial_handle_plug_req(struct work_struct *work)
{
	struct fwtty_peer *peer = to_peer(work, work);
	struct virt_plug_params *plug_req = &peer->work_params.plug_req;
	struct fwtty_port *port;
	struct fwserial_mgmt_pkt *pkt;
	int rcode;

	pkt = kmalloc(sizeof(*pkt), GFP_KERNEL);
	if (!pkt)
		return;

	port = fwserial_find_port(peer);

	spin_lock_bh(&peer->lock);

	switch (peer->state) {
	case FWPS_NOT_ATTACHED:
		if (!port) {
			fwtty_err(&peer->unit, "no more ports avail\n");
			fill_plug_rsp_nack(pkt);
		} else {
			peer->port = port;
			fill_plug_rsp_ok(pkt, peer->port);
			peer_set_state(peer, FWPS_PLUG_RESPONDING);
			/* don't release claimed port */
			port = NULL;
		}
		break;

	case FWPS_PLUG_PENDING:
		if (peer->serial->card->guid > peer->guid)
			goto cleanup;

		/* We lost - hijack the already-claimed port and send ok */
		del_timer(&peer->timer);
		fill_plug_rsp_ok(pkt, peer->port);
		peer_set_state(peer, FWPS_PLUG_RESPONDING);
		break;

	default:
		fill_plug_rsp_nack(pkt);
	}

	spin_unlock_bh(&peer->lock);
	if (port)
		fwserial_release_port(port, false);

	rcode = fwserial_send_mgmt_sync(peer, pkt);

	spin_lock_bh(&peer->lock);
	if (peer->state == FWPS_PLUG_RESPONDING) {
		if (rcode == RCODE_COMPLETE) {
			struct fwtty_port *tmp = peer->port;

			fwserial_virt_plug_complete(peer, plug_req);
			spin_unlock_bh(&peer->lock);

			fwtty_write_port_status(tmp);
			spin_lock_bh(&peer->lock);
		} else {
			fwtty_err(&peer->unit, "PLUG_RSP error (%d)\n", rcode);
			port = peer_revert_state(peer);
		}
	}
cleanup:
	spin_unlock_bh(&peer->lock);
	if (port)
		fwserial_release_port(port, false);
	kfree(pkt);
}