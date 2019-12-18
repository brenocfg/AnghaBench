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
struct l2cap_chan {scalar_t__ mode; int /*<<< orphan*/  srej_list; int /*<<< orphan*/  remote_tx_win; int /*<<< orphan*/  retrans_list; int /*<<< orphan*/  tx_win; int /*<<< orphan*/  srej_q; int /*<<< orphan*/  ack_timer; int /*<<< orphan*/  monitor_timer; int /*<<< orphan*/  retrans_timer; int /*<<< orphan*/  tx_state; int /*<<< orphan*/  rx_state; int /*<<< orphan*/  move_role; int /*<<< orphan*/  move_state; void* move_id; void* local_amp_id; int /*<<< orphan*/  tx_q; scalar_t__ sdu_len; int /*<<< orphan*/ * sdu_last_frag; int /*<<< orphan*/ * sdu; scalar_t__ last_acked_seq; scalar_t__ frames_sent; scalar_t__ buffer_seq; scalar_t__ unacked_frames; scalar_t__ expected_ack_seq; scalar_t__ expected_tx_seq; scalar_t__ next_tx_seq; } ;

/* Variables and functions */
 void* AMP_ID_BREDR ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ L2CAP_MODE_ERTM ; 
 int /*<<< orphan*/  L2CAP_MOVE_ROLE_NONE ; 
 int /*<<< orphan*/  L2CAP_MOVE_STABLE ; 
 int /*<<< orphan*/  L2CAP_RX_STATE_RECV ; 
 int /*<<< orphan*/  L2CAP_TX_STATE_XMIT ; 
 int /*<<< orphan*/  l2cap_ack_timeout ; 
 int /*<<< orphan*/  l2cap_monitor_timeout ; 
 int /*<<< orphan*/  l2cap_retrans_timeout ; 
 int /*<<< orphan*/  l2cap_seq_list_free (int /*<<< orphan*/ *) ; 
 int l2cap_seq_list_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

int l2cap_ertm_init(struct l2cap_chan *chan)
{
	int err;

	chan->next_tx_seq = 0;
	chan->expected_tx_seq = 0;
	chan->expected_ack_seq = 0;
	chan->unacked_frames = 0;
	chan->buffer_seq = 0;
	chan->frames_sent = 0;
	chan->last_acked_seq = 0;
	chan->sdu = NULL;
	chan->sdu_last_frag = NULL;
	chan->sdu_len = 0;

	skb_queue_head_init(&chan->tx_q);

	chan->local_amp_id = AMP_ID_BREDR;
	chan->move_id = AMP_ID_BREDR;
	chan->move_state = L2CAP_MOVE_STABLE;
	chan->move_role = L2CAP_MOVE_ROLE_NONE;

	if (chan->mode != L2CAP_MODE_ERTM)
		return 0;

	chan->rx_state = L2CAP_RX_STATE_RECV;
	chan->tx_state = L2CAP_TX_STATE_XMIT;

	INIT_DELAYED_WORK(&chan->retrans_timer, l2cap_retrans_timeout);
	INIT_DELAYED_WORK(&chan->monitor_timer, l2cap_monitor_timeout);
	INIT_DELAYED_WORK(&chan->ack_timer, l2cap_ack_timeout);

	skb_queue_head_init(&chan->srej_q);

	err = l2cap_seq_list_init(&chan->srej_list, chan->tx_win);
	if (err < 0)
		return err;

	err = l2cap_seq_list_init(&chan->retrans_list, chan->remote_tx_win);
	if (err < 0)
		l2cap_seq_list_free(&chan->srej_list);

	return err;
}