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
typedef  int u16 ;
struct l2cap_move_chan_cfm_rsp {int /*<<< orphan*/  icid; } ;
struct l2cap_conn {int dummy; } ;
struct l2cap_cmd_hdr {int dummy; } ;
struct l2cap_chan {scalar_t__ move_state; scalar_t__ local_amp_id; scalar_t__ move_id; scalar_t__ hs_hchan; } ;

/* Variables and functions */
 scalar_t__ AMP_ID_BREDR ; 
 int /*<<< orphan*/  BT_DBG (char*,int) ; 
 int EPROTO ; 
 scalar_t__ L2CAP_MOVE_WAIT_CONFIRM_RSP ; 
 int /*<<< orphan*/  __clear_chan_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  __release_logical_link (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 struct l2cap_chan* l2cap_get_chan_by_scid (struct l2cap_conn*,int) ; 
 int /*<<< orphan*/  l2cap_move_done (struct l2cap_chan*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int l2cap_move_channel_confirm_rsp(struct l2cap_conn *conn,
						 struct l2cap_cmd_hdr *cmd,
						 u16 cmd_len, void *data)
{
	struct l2cap_move_chan_cfm_rsp *rsp = data;
	struct l2cap_chan *chan;
	u16 icid;

	if (cmd_len != sizeof(*rsp))
		return -EPROTO;

	icid = le16_to_cpu(rsp->icid);

	BT_DBG("icid 0x%4.4x", icid);

	chan = l2cap_get_chan_by_scid(conn, icid);
	if (!chan)
		return 0;

	__clear_chan_timer(chan);

	if (chan->move_state == L2CAP_MOVE_WAIT_CONFIRM_RSP) {
		chan->local_amp_id = chan->move_id;

		if (chan->local_amp_id == AMP_ID_BREDR && chan->hs_hchan)
			__release_logical_link(chan);

		l2cap_move_done(chan);
	}

	l2cap_chan_unlock(chan);

	return 0;
}