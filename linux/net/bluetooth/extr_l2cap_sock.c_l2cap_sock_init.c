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
struct sock {int sk_type; } ;
struct l2cap_chan {int /*<<< orphan*/ * ops; struct sock* data; int /*<<< orphan*/  flush_to; int /*<<< orphan*/  mode; int /*<<< orphan*/  conf_state; scalar_t__ omtu; int /*<<< orphan*/  imtu; int /*<<< orphan*/  chan_type; int /*<<< orphan*/  scid; int /*<<< orphan*/  dcid; int /*<<< orphan*/  rx_credits; int /*<<< orphan*/  tx_credits; int /*<<< orphan*/  flags; int /*<<< orphan*/  sec_level; int /*<<< orphan*/  tx_win_max; int /*<<< orphan*/  tx_win; int /*<<< orphan*/  max_tx; int /*<<< orphan*/  fcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  skb_msg_name; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {struct l2cap_chan* chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*) ; 
 int /*<<< orphan*/  CONF_STATE2_DEVICE ; 
 int /*<<< orphan*/  L2CAP_CHAN_CONN_LESS ; 
 int /*<<< orphan*/  L2CAP_CHAN_CONN_ORIENTED ; 
 int /*<<< orphan*/  L2CAP_CHAN_FIXED ; 
 int /*<<< orphan*/  L2CAP_CHAN_RAW ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_FLUSH_TO ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_MTU ; 
 int /*<<< orphan*/  L2CAP_MODE_BASIC ; 
 int /*<<< orphan*/  L2CAP_MODE_ERTM ; 
#define  SOCK_DGRAM 131 
#define  SOCK_RAW 130 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 TYPE_2__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  disable_ertm ; 
 int /*<<< orphan*/  l2cap_chan_ops ; 
 int /*<<< orphan*/  l2cap_chan_set_defaults (struct l2cap_chan*) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  l2cap_skb_msg_name ; 
 int /*<<< orphan*/  security_sk_clone (struct sock*,struct sock*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_sock_init(struct sock *sk, struct sock *parent)
{
	struct l2cap_chan *chan = l2cap_pi(sk)->chan;

	BT_DBG("sk %p", sk);

	if (parent) {
		struct l2cap_chan *pchan = l2cap_pi(parent)->chan;

		sk->sk_type = parent->sk_type;
		bt_sk(sk)->flags = bt_sk(parent)->flags;

		chan->chan_type = pchan->chan_type;
		chan->imtu = pchan->imtu;
		chan->omtu = pchan->omtu;
		chan->conf_state = pchan->conf_state;
		chan->mode = pchan->mode;
		chan->fcs  = pchan->fcs;
		chan->max_tx = pchan->max_tx;
		chan->tx_win = pchan->tx_win;
		chan->tx_win_max = pchan->tx_win_max;
		chan->sec_level = pchan->sec_level;
		chan->flags = pchan->flags;
		chan->tx_credits = pchan->tx_credits;
		chan->rx_credits = pchan->rx_credits;

		if (chan->chan_type == L2CAP_CHAN_FIXED) {
			chan->scid = pchan->scid;
			chan->dcid = pchan->scid;
		}

		security_sk_clone(parent, sk);
	} else {
		switch (sk->sk_type) {
		case SOCK_RAW:
			chan->chan_type = L2CAP_CHAN_RAW;
			break;
		case SOCK_DGRAM:
			chan->chan_type = L2CAP_CHAN_CONN_LESS;
			bt_sk(sk)->skb_msg_name = l2cap_skb_msg_name;
			break;
		case SOCK_SEQPACKET:
		case SOCK_STREAM:
			chan->chan_type = L2CAP_CHAN_CONN_ORIENTED;
			break;
		}

		chan->imtu = L2CAP_DEFAULT_MTU;
		chan->omtu = 0;
		if (!disable_ertm && sk->sk_type == SOCK_STREAM) {
			chan->mode = L2CAP_MODE_ERTM;
			set_bit(CONF_STATE2_DEVICE, &chan->conf_state);
		} else {
			chan->mode = L2CAP_MODE_BASIC;
		}

		l2cap_chan_set_defaults(chan);
	}

	/* Default config options */
	chan->flush_to = L2CAP_DEFAULT_FLUSH_TO;

	chan->data = sk;
	chan->ops = &l2cap_chan_ops;
}