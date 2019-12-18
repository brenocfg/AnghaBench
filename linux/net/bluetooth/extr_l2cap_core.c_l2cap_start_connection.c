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
struct l2cap_chan {TYPE_2__* conn; } ;
struct TYPE_4__ {TYPE_1__* hcon; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 scalar_t__ LE_LINK ; 
 scalar_t__ __amp_capable (struct l2cap_chan*) ; 
 int /*<<< orphan*/  a2mp_discover_amp (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_le_start (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_conn_req (struct l2cap_chan*) ; 

__attribute__((used)) static void l2cap_start_connection(struct l2cap_chan *chan)
{
	if (__amp_capable(chan)) {
		BT_DBG("chan %p AMP capable: discover AMPs", chan);
		a2mp_discover_amp(chan);
	} else if (chan->conn->hcon->type == LE_LINK) {
		l2cap_le_start(chan);
	} else {
		l2cap_send_conn_req(chan);
	}
}