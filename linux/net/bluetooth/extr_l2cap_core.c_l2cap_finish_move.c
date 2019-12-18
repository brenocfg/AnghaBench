#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct l2cap_chan {TYPE_4__* conn; TYPE_3__* hs_hcon; int /*<<< orphan*/  rx_state; } ;
struct TYPE_10__ {int /*<<< orphan*/  acl_mtu; } ;
struct TYPE_9__ {TYPE_1__* hcon; int /*<<< orphan*/  mtu; } ;
struct TYPE_8__ {TYPE_2__* hdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  block_mtu; } ;
struct TYPE_6__ {TYPE_5__* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  L2CAP_RX_STATE_RECV ; 
 int l2cap_resegment (struct l2cap_chan*) ; 

__attribute__((used)) static int l2cap_finish_move(struct l2cap_chan *chan)
{
	BT_DBG("chan %p", chan);

	chan->rx_state = L2CAP_RX_STATE_RECV;

	if (chan->hs_hcon)
		chan->conn->mtu = chan->hs_hcon->hdev->block_mtu;
	else
		chan->conn->mtu = chan->conn->hcon->hdev->acl_mtu;

	return l2cap_resegment(chan);
}