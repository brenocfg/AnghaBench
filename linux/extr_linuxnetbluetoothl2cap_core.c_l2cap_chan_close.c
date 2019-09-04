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
struct l2cap_conn {TYPE_1__* hcon; } ;
struct l2cap_chan {int state; TYPE_2__* ops; int /*<<< orphan*/  chan_type; struct l2cap_conn* conn; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* teardown ) (struct l2cap_chan*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_sndtimeo ) (struct l2cap_chan*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
#define  BT_CONFIG 133 
#define  BT_CONNECT 132 
#define  BT_CONNECT2 131 
#define  BT_CONNECTED 130 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,int /*<<< orphan*/ ) ; 
#define  BT_DISCONN 129 
#define  BT_LISTEN 128 
 int /*<<< orphan*/  L2CAP_CHAN_CONN_ORIENTED ; 
 int /*<<< orphan*/  LE_LINK ; 
 int /*<<< orphan*/  __set_chan_timer (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_connect_reject (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct l2cap_chan*,int) ; 
 int /*<<< orphan*/  l2cap_chan_le_connect_reject (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int) ; 
 int /*<<< orphan*/  state_to_string (int) ; 
 int /*<<< orphan*/  stub1 (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct l2cap_chan*) ; 
 int /*<<< orphan*/  stub3 (struct l2cap_chan*,int /*<<< orphan*/ ) ; 

void l2cap_chan_close(struct l2cap_chan *chan, int reason)
{
	struct l2cap_conn *conn = chan->conn;

	BT_DBG("chan %p state %s", chan, state_to_string(chan->state));

	switch (chan->state) {
	case BT_LISTEN:
		chan->ops->teardown(chan, 0);
		break;

	case BT_CONNECTED:
	case BT_CONFIG:
		if (chan->chan_type == L2CAP_CHAN_CONN_ORIENTED) {
			__set_chan_timer(chan, chan->ops->get_sndtimeo(chan));
			l2cap_send_disconn_req(chan, reason);
		} else
			l2cap_chan_del(chan, reason);
		break;

	case BT_CONNECT2:
		if (chan->chan_type == L2CAP_CHAN_CONN_ORIENTED) {
			if (conn->hcon->type == ACL_LINK)
				l2cap_chan_connect_reject(chan);
			else if (conn->hcon->type == LE_LINK)
				l2cap_chan_le_connect_reject(chan);
		}

		l2cap_chan_del(chan, reason);
		break;

	case BT_CONNECT:
	case BT_DISCONN:
		l2cap_chan_del(chan, reason);
		break;

	default:
		chan->ops->teardown(chan, 0);
		break;
	}
}