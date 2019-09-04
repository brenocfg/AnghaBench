#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct l2cap_conn {TYPE_1__* hcon; } ;
struct l2cap_chan {struct l2cap_conn* conn; } ;
struct amp_mgr {struct l2cap_chan* bredr_chan; } ;
struct a2mp_discov_req {scalar_t__ ext_feat; int /*<<< orphan*/  mtu; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {struct amp_mgr* amp_mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  A2MP_DISCOVER_REQ ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,struct l2cap_conn*,struct amp_mgr*) ; 
 int /*<<< orphan*/  L2CAP_A2MP_DEFAULT_MTU ; 
 int /*<<< orphan*/  a2mp_send (struct amp_mgr*,int /*<<< orphan*/ ,int,int,struct a2mp_discov_req*) ; 
 struct amp_mgr* amp_mgr_create (struct l2cap_conn*,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

void a2mp_discover_amp(struct l2cap_chan *chan)
{
	struct l2cap_conn *conn = chan->conn;
	struct amp_mgr *mgr = conn->hcon->amp_mgr;
	struct a2mp_discov_req req;

	BT_DBG("chan %p conn %p mgr %p", chan, conn, mgr);

	if (!mgr) {
		mgr = amp_mgr_create(conn, true);
		if (!mgr)
			return;
	}

	mgr->bredr_chan = chan;

	req.mtu = cpu_to_le16(L2CAP_A2MP_DEFAULT_MTU);
	req.ext_feat = 0;
	a2mp_send(mgr, A2MP_DISCOVER_REQ, 1, sizeof(req), &req);
}