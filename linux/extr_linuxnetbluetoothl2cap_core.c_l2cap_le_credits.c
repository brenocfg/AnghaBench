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
struct l2cap_le_credits {int /*<<< orphan*/  credits; int /*<<< orphan*/  cid; } ;
struct l2cap_conn {int dummy; } ;
struct l2cap_cmd_hdr {int dummy; } ;
struct l2cap_chan {int tx_credits; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct l2cap_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int EBADSLT ; 
 int /*<<< orphan*/  ECONNRESET ; 
 int EPROTO ; 
 int LE_FLOWCTL_MAX_CREDITS ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 struct l2cap_chan* l2cap_get_chan_by_dcid (struct l2cap_conn*,int) ; 
 int /*<<< orphan*/  l2cap_le_flowctl_send (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_send_disconn_req (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct l2cap_chan*) ; 

__attribute__((used)) static inline int l2cap_le_credits(struct l2cap_conn *conn,
				   struct l2cap_cmd_hdr *cmd, u16 cmd_len,
				   u8 *data)
{
	struct l2cap_le_credits *pkt;
	struct l2cap_chan *chan;
	u16 cid, credits, max_credits;

	if (cmd_len != sizeof(*pkt))
		return -EPROTO;

	pkt = (struct l2cap_le_credits *) data;
	cid	= __le16_to_cpu(pkt->cid);
	credits	= __le16_to_cpu(pkt->credits);

	BT_DBG("cid 0x%4.4x credits 0x%4.4x", cid, credits);

	chan = l2cap_get_chan_by_dcid(conn, cid);
	if (!chan)
		return -EBADSLT;

	max_credits = LE_FLOWCTL_MAX_CREDITS - chan->tx_credits;
	if (credits > max_credits) {
		BT_ERR("LE credits overflow");
		l2cap_send_disconn_req(chan, ECONNRESET);
		l2cap_chan_unlock(chan);

		/* Return 0 so that we don't trigger an unnecessary
		 * command reject packet.
		 */
		return 0;
	}

	chan->tx_credits += credits;

	/* Resume sending */
	l2cap_le_flowctl_send(chan);

	if (chan->tx_credits)
		chan->ops->resume(chan);

	l2cap_chan_unlock(chan);

	return 0;
}