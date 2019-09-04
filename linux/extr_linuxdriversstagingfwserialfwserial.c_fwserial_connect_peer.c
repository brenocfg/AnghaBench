#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fwtty_port {int dummy; } ;
struct fwtty_peer {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; struct fwtty_port* port; int /*<<< orphan*/  unit; } ;
struct fwserial_mgmt_pkt {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ FWPS_NOT_ATTACHED ; 
 scalar_t__ FWPS_PLUG_PENDING ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RCODE_COMPLETE ; 
 int RCODE_CONFLICT_ERROR ; 
 scalar_t__ VIRT_CABLE_PLUG_TIMEOUT ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_plug_req (struct fwserial_mgmt_pkt*,struct fwtty_port*) ; 
 struct fwtty_port* fwserial_find_port (struct fwtty_peer*) ; 
 int /*<<< orphan*/  fwserial_release_port (struct fwtty_port*,int) ; 
 int fwserial_send_mgmt_sync (struct fwtty_peer*,struct fwserial_mgmt_pkt*) ; 
 int /*<<< orphan*/  fwtty_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct fwserial_mgmt_pkt*) ; 
 struct fwserial_mgmt_pkt* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  peer_revert_state (struct fwtty_peer*) ; 
 int /*<<< orphan*/  peer_set_state (struct fwtty_peer*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fwserial_connect_peer(struct fwtty_peer *peer)
{
	struct fwtty_port *port;
	struct fwserial_mgmt_pkt *pkt;
	int err, rcode;

	pkt = kmalloc(sizeof(*pkt), GFP_KERNEL);
	if (!pkt)
		return -ENOMEM;

	port = fwserial_find_port(peer);
	if (!port) {
		fwtty_err(&peer->unit, "avail ports in use\n");
		err = -EBUSY;
		goto free_pkt;
	}

	spin_lock_bh(&peer->lock);

	/* only initiate VIRT_CABLE_PLUG if peer is currently not attached */
	if (peer->state != FWPS_NOT_ATTACHED) {
		err = -EBUSY;
		goto release_port;
	}

	peer->port = port;
	peer_set_state(peer, FWPS_PLUG_PENDING);

	fill_plug_req(pkt, peer->port);

	mod_timer(&peer->timer, jiffies + VIRT_CABLE_PLUG_TIMEOUT);
	spin_unlock_bh(&peer->lock);

	rcode = fwserial_send_mgmt_sync(peer, pkt);

	spin_lock_bh(&peer->lock);
	if (peer->state == FWPS_PLUG_PENDING && rcode != RCODE_COMPLETE) {
		if (rcode == RCODE_CONFLICT_ERROR)
			err = -EAGAIN;
		else
			err = -EIO;
		goto cancel_timer;
	}
	spin_unlock_bh(&peer->lock);

	kfree(pkt);
	return 0;

cancel_timer:
	del_timer(&peer->timer);
	peer_revert_state(peer);
release_port:
	spin_unlock_bh(&peer->lock);
	fwserial_release_port(port, false);
free_pkt:
	kfree(pkt);
	return err;
}