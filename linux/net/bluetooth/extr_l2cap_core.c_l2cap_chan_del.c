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
struct l2cap_conn {TYPE_2__* hcon; } ;
struct l2cap_chan {scalar_t__ chan_type; int mode; int /*<<< orphan*/  tx_q; int /*<<< orphan*/  retrans_list; int /*<<< orphan*/  srej_list; int /*<<< orphan*/  srej_q; int /*<<< orphan*/  conf_state; struct hci_chan* hs_hchan; int /*<<< orphan*/  flags; struct l2cap_conn* conn; int /*<<< orphan*/  list; TYPE_1__* ops; int /*<<< orphan*/  state; } ;
struct hci_chan {int dummy; } ;
struct amp_mgr {struct l2cap_chan* bredr_chan; } ;
struct TYPE_4__ {struct amp_mgr* amp_mgr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* teardown ) (struct l2cap_chan*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,struct l2cap_conn*,...) ; 
 int /*<<< orphan*/  CONF_NOT_COMPLETE ; 
 int /*<<< orphan*/  FLAG_HOLD_HCI_CONN ; 
 scalar_t__ L2CAP_CHAN_FIXED ; 
#define  L2CAP_MODE_BASIC 131 
#define  L2CAP_MODE_ERTM 130 
#define  L2CAP_MODE_LE_FLOWCTL 129 
#define  L2CAP_MODE_STREAMING 128 
 int /*<<< orphan*/  __clear_ack_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __clear_chan_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __clear_monitor_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __clear_retrans_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  amp_disconnect_logical_link (struct hci_chan*) ; 
 int /*<<< orphan*/  hci_conn_drop (TYPE_2__*) ; 
 int /*<<< orphan*/  l2cap_chan_put (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_seq_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  state_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct l2cap_chan*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void l2cap_chan_del(struct l2cap_chan *chan, int err)
{
	struct l2cap_conn *conn = chan->conn;

	__clear_chan_timer(chan);

	BT_DBG("chan %p, conn %p, err %d, state %s", chan, conn, err,
	       state_to_string(chan->state));

	chan->ops->teardown(chan, err);

	if (conn) {
		struct amp_mgr *mgr = conn->hcon->amp_mgr;
		/* Delete from channel list */
		list_del(&chan->list);

		l2cap_chan_put(chan);

		chan->conn = NULL;

		/* Reference was only held for non-fixed channels or
		 * fixed channels that explicitly requested it using the
		 * FLAG_HOLD_HCI_CONN flag.
		 */
		if (chan->chan_type != L2CAP_CHAN_FIXED ||
		    test_bit(FLAG_HOLD_HCI_CONN, &chan->flags))
			hci_conn_drop(conn->hcon);

		if (mgr && mgr->bredr_chan == chan)
			mgr->bredr_chan = NULL;
	}

	if (chan->hs_hchan) {
		struct hci_chan *hs_hchan = chan->hs_hchan;

		BT_DBG("chan %p disconnect hs_hchan %p", chan, hs_hchan);
		amp_disconnect_logical_link(hs_hchan);
	}

	if (test_bit(CONF_NOT_COMPLETE, &chan->conf_state))
		return;

	switch(chan->mode) {
	case L2CAP_MODE_BASIC:
		break;

	case L2CAP_MODE_LE_FLOWCTL:
		skb_queue_purge(&chan->tx_q);
		break;

	case L2CAP_MODE_ERTM:
		__clear_retrans_timer(chan);
		__clear_monitor_timer(chan);
		__clear_ack_timer(chan);

		skb_queue_purge(&chan->srej_q);

		l2cap_seq_list_free(&chan->srej_list);
		l2cap_seq_list_free(&chan->retrans_list);

		/* fall through */

	case L2CAP_MODE_STREAMING:
		skb_queue_purge(&chan->tx_q);
		break;
	}

	return;
}