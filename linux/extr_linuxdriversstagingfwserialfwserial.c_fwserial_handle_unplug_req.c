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
struct work_struct {int dummy; } ;
struct fwtty_port {int dummy; } ;
struct fwtty_peer {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  unit; int /*<<< orphan*/  timer; int /*<<< orphan*/  guid; TYPE_2__* serial; } ;
struct fwserial_mgmt_pkt {int dummy; } ;
struct TYPE_4__ {TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  guid; } ;

/* Variables and functions */
#define  FWPS_ATTACHED 129 
#define  FWPS_UNPLUG_PENDING 128 
 int FWPS_UNPLUG_RESPONDING ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_unplug_rsp_nack (struct fwserial_mgmt_pkt*) ; 
 int /*<<< orphan*/  fill_unplug_rsp_ok (struct fwserial_mgmt_pkt*) ; 
 int /*<<< orphan*/  fwserial_release_port (struct fwtty_port*,int) ; 
 int fwserial_send_mgmt_sync (struct fwtty_peer*,struct fwserial_mgmt_pkt*) ; 
 int /*<<< orphan*/  fwtty_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (struct fwserial_mgmt_pkt*) ; 
 struct fwserial_mgmt_pkt* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct fwtty_port* peer_revert_state (struct fwtty_peer*) ; 
 int /*<<< orphan*/  peer_set_state (struct fwtty_peer*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct fwtty_peer* to_peer (struct work_struct*,struct work_struct*) ; 

__attribute__((used)) static void fwserial_handle_unplug_req(struct work_struct *work)
{
	struct fwtty_peer *peer = to_peer(work, work);
	struct fwtty_port *port = NULL;
	struct fwserial_mgmt_pkt *pkt;
	int rcode;

	pkt = kmalloc(sizeof(*pkt), GFP_KERNEL);
	if (!pkt)
		return;

	spin_lock_bh(&peer->lock);

	switch (peer->state) {
	case FWPS_ATTACHED:
		fill_unplug_rsp_ok(pkt);
		peer_set_state(peer, FWPS_UNPLUG_RESPONDING);
		break;

	case FWPS_UNPLUG_PENDING:
		if (peer->serial->card->guid > peer->guid)
			goto cleanup;

		/* We lost - send unplug rsp */
		del_timer(&peer->timer);
		fill_unplug_rsp_ok(pkt);
		peer_set_state(peer, FWPS_UNPLUG_RESPONDING);
		break;

	default:
		fill_unplug_rsp_nack(pkt);
	}

	spin_unlock_bh(&peer->lock);

	rcode = fwserial_send_mgmt_sync(peer, pkt);

	spin_lock_bh(&peer->lock);
	if (peer->state == FWPS_UNPLUG_RESPONDING) {
		if (rcode != RCODE_COMPLETE)
			fwtty_err(&peer->unit, "UNPLUG_RSP error (%d)\n",
				  rcode);
		port = peer_revert_state(peer);
	}
cleanup:
	spin_unlock_bh(&peer->lock);
	if (port)
		fwserial_release_port(port, true);
	kfree(pkt);
}