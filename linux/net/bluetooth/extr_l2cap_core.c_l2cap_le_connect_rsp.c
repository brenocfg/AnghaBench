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
struct l2cap_le_conn_rsp {int /*<<< orphan*/  result; int /*<<< orphan*/  credits; int /*<<< orphan*/  mps; int /*<<< orphan*/  mtu; int /*<<< orphan*/  dcid; } ;
struct l2cap_conn {int /*<<< orphan*/  chan_lock; struct hci_conn* hcon; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; } ;
struct l2cap_chan {int dcid; int omtu; int remote_mps; int tx_credits; int sec_level; int /*<<< orphan*/  flags; int /*<<< orphan*/  ident; } ;
struct hci_conn {int /*<<< orphan*/  sec_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  BT_SECURITY_MEDIUM ; 
 int EBADSLT ; 
 int /*<<< orphan*/  ECONNREFUSED ; 
 int EPROTO ; 
 int /*<<< orphan*/  FLAG_LE_CONN_REQ_SENT ; 
 int L2CAP_CID_DYN_START ; 
 int L2CAP_CID_LE_DYN_END ; 
#define  L2CAP_CR_LE_AUTHENTICATION 130 
#define  L2CAP_CR_LE_ENCRYPTION 129 
#define  L2CAP_CR_LE_SUCCESS 128 
 int /*<<< orphan*/  __l2cap_get_chan_by_dcid (struct l2cap_conn*,int) ; 
 struct l2cap_chan* __l2cap_get_chan_by_ident (struct l2cap_conn*,int /*<<< orphan*/ ) ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_ready (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_conn_security (struct hci_conn*,int) ; 

__attribute__((used)) static int l2cap_le_connect_rsp(struct l2cap_conn *conn,
				struct l2cap_cmd_hdr *cmd, u16 cmd_len,
				u8 *data)
{
	struct l2cap_le_conn_rsp *rsp = (struct l2cap_le_conn_rsp *) data;
	struct hci_conn *hcon = conn->hcon;
	u16 dcid, mtu, mps, credits, result;
	struct l2cap_chan *chan;
	int err, sec_level;

	if (cmd_len < sizeof(*rsp))
		return -EPROTO;

	dcid    = __le16_to_cpu(rsp->dcid);
	mtu     = __le16_to_cpu(rsp->mtu);
	mps     = __le16_to_cpu(rsp->mps);
	credits = __le16_to_cpu(rsp->credits);
	result  = __le16_to_cpu(rsp->result);

	if (result == L2CAP_CR_LE_SUCCESS && (mtu < 23 || mps < 23 ||
					   dcid < L2CAP_CID_DYN_START ||
					   dcid > L2CAP_CID_LE_DYN_END))
		return -EPROTO;

	BT_DBG("dcid 0x%4.4x mtu %u mps %u credits %u result 0x%2.2x",
	       dcid, mtu, mps, credits, result);

	mutex_lock(&conn->chan_lock);

	chan = __l2cap_get_chan_by_ident(conn, cmd->ident);
	if (!chan) {
		err = -EBADSLT;
		goto unlock;
	}

	err = 0;

	l2cap_chan_lock(chan);

	switch (result) {
	case L2CAP_CR_LE_SUCCESS:
		if (__l2cap_get_chan_by_dcid(conn, dcid)) {
			err = -EBADSLT;
			break;
		}

		chan->ident = 0;
		chan->dcid = dcid;
		chan->omtu = mtu;
		chan->remote_mps = mps;
		chan->tx_credits = credits;
		l2cap_chan_ready(chan);
		break;

	case L2CAP_CR_LE_AUTHENTICATION:
	case L2CAP_CR_LE_ENCRYPTION:
		/* If we already have MITM protection we can't do
		 * anything.
		 */
		if (hcon->sec_level > BT_SECURITY_MEDIUM) {
			l2cap_chan_del(chan, ECONNREFUSED);
			break;
		}

		sec_level = hcon->sec_level + 1;
		if (chan->sec_level < sec_level)
			chan->sec_level = sec_level;

		/* We'll need to send a new Connect Request */
		clear_bit(FLAG_LE_CONN_REQ_SENT, &chan->flags);

		smp_conn_security(hcon, chan->sec_level);
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