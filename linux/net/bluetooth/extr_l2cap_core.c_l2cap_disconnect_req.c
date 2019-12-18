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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct l2cap_disconn_rsp {void* scid; void* dcid; } ;
struct l2cap_disconn_req {int /*<<< orphan*/  dcid; int /*<<< orphan*/  scid; } ;
struct l2cap_conn {int /*<<< orphan*/  chan_lock; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; } ;
struct l2cap_chan {TYPE_1__* ops; int /*<<< orphan*/  dcid; int /*<<< orphan*/  scid; } ;
typedef  int /*<<< orphan*/  rsp ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct l2cap_chan*) ;int /*<<< orphan*/  (* set_shutdown ) (struct l2cap_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int) ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int EPROTO ; 
 int /*<<< orphan*/  L2CAP_DISCONN_RSP ; 
 struct l2cap_chan* __l2cap_get_chan_by_scid (struct l2cap_conn*,int) ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_reject_invalid_cid (struct l2cap_conn*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_hold (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_put (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct l2cap_disconn_rsp*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct l2cap_chan*) ; 
 int /*<<< orphan*/  stub2 (struct l2cap_chan*) ; 

__attribute__((used)) static inline int l2cap_disconnect_req(struct l2cap_conn *conn,
				       struct l2cap_cmd_hdr *cmd, u16 cmd_len,
				       u8 *data)
{
	struct l2cap_disconn_req *req = (struct l2cap_disconn_req *) data;
	struct l2cap_disconn_rsp rsp;
	u16 dcid, scid;
	struct l2cap_chan *chan;

	if (cmd_len != sizeof(*req))
		return -EPROTO;

	scid = __le16_to_cpu(req->scid);
	dcid = __le16_to_cpu(req->dcid);

	BT_DBG("scid 0x%4.4x dcid 0x%4.4x", scid, dcid);

	mutex_lock(&conn->chan_lock);

	chan = __l2cap_get_chan_by_scid(conn, dcid);
	if (!chan) {
		mutex_unlock(&conn->chan_lock);
		cmd_reject_invalid_cid(conn, cmd->ident, dcid, scid);
		return 0;
	}

	l2cap_chan_lock(chan);

	rsp.dcid = cpu_to_le16(chan->scid);
	rsp.scid = cpu_to_le16(chan->dcid);
	l2cap_send_cmd(conn, cmd->ident, L2CAP_DISCONN_RSP, sizeof(rsp), &rsp);

	chan->ops->set_shutdown(chan);

	l2cap_chan_hold(chan);
	l2cap_chan_del(chan, ECONNRESET);

	l2cap_chan_unlock(chan);

	chan->ops->close(chan);
	l2cap_chan_put(chan);

	mutex_unlock(&conn->chan_lock);

	return 0;
}