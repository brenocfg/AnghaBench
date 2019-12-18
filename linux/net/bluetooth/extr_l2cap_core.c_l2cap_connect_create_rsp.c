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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct l2cap_conn_rsp {int /*<<< orphan*/  status; int /*<<< orphan*/  result; int /*<<< orphan*/  dcid; int /*<<< orphan*/  scid; } ;
struct l2cap_conn {int /*<<< orphan*/  chan_lock; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; } ;
struct l2cap_chan {int dcid; int /*<<< orphan*/  conf_state; int /*<<< orphan*/  num_conf_req; int /*<<< orphan*/  ident; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CONFIG ; 
 int /*<<< orphan*/  BT_DBG (char*,int,int,int,int) ; 
 int /*<<< orphan*/  CONF_CONNECT_PEND ; 
 int /*<<< orphan*/  CONF_REQ_SENT ; 
 int EBADSLT ; 
 int /*<<< orphan*/  ECONNREFUSED ; 
 int EPROTO ; 
 int /*<<< orphan*/  L2CAP_CONF_REQ ; 
#define  L2CAP_CR_PEND 129 
#define  L2CAP_CR_SUCCESS 128 
 struct l2cap_chan* __l2cap_get_chan_by_ident (struct l2cap_conn*,int /*<<< orphan*/ ) ; 
 struct l2cap_chan* __l2cap_get_chan_by_scid (struct l2cap_conn*,int) ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_build_conf_req (struct l2cap_chan*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_get_ident (struct l2cap_conn*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_state_change (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2cap_connect_create_rsp(struct l2cap_conn *conn,
				    struct l2cap_cmd_hdr *cmd, u16 cmd_len,
				    u8 *data)
{
	struct l2cap_conn_rsp *rsp = (struct l2cap_conn_rsp *) data;
	u16 scid, dcid, result, status;
	struct l2cap_chan *chan;
	u8 req[128];
	int err;

	if (cmd_len < sizeof(*rsp))
		return -EPROTO;

	scid   = __le16_to_cpu(rsp->scid);
	dcid   = __le16_to_cpu(rsp->dcid);
	result = __le16_to_cpu(rsp->result);
	status = __le16_to_cpu(rsp->status);

	BT_DBG("dcid 0x%4.4x scid 0x%4.4x result 0x%2.2x status 0x%2.2x",
	       dcid, scid, result, status);

	mutex_lock(&conn->chan_lock);

	if (scid) {
		chan = __l2cap_get_chan_by_scid(conn, scid);
		if (!chan) {
			err = -EBADSLT;
			goto unlock;
		}
	} else {
		chan = __l2cap_get_chan_by_ident(conn, cmd->ident);
		if (!chan) {
			err = -EBADSLT;
			goto unlock;
		}
	}

	err = 0;

	l2cap_chan_lock(chan);

	switch (result) {
	case L2CAP_CR_SUCCESS:
		l2cap_state_change(chan, BT_CONFIG);
		chan->ident = 0;
		chan->dcid = dcid;
		clear_bit(CONF_CONNECT_PEND, &chan->conf_state);

		if (test_and_set_bit(CONF_REQ_SENT, &chan->conf_state))
			break;

		l2cap_send_cmd(conn, l2cap_get_ident(conn), L2CAP_CONF_REQ,
			       l2cap_build_conf_req(chan, req, sizeof(req)), req);
		chan->num_conf_req++;
		break;

	case L2CAP_CR_PEND:
		set_bit(CONF_CONNECT_PEND, &chan->conf_state);
		break;

	default:
		l2cap_chan_del(chan, ECONNREFUSED);
		break;
	}

	l2cap_chan_unlock(chan);

unlock:
	mutex_unlock(&conn->chan_lock);

	return err;
}