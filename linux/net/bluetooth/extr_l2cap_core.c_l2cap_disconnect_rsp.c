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
struct l2cap_disconn_rsp {int /*<<< orphan*/  dcid; int /*<<< orphan*/  scid; } ;
struct l2cap_conn {int /*<<< orphan*/  chan_lock; } ;
struct l2cap_cmd_hdr {int dummy; } ;
struct l2cap_chan {scalar_t__ state; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct l2cap_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int,int) ; 
 scalar_t__ BT_DISCONN ; 
 int EPROTO ; 
 struct l2cap_chan* __l2cap_get_chan_by_scid (struct l2cap_conn*,int) ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_hold (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_put (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct l2cap_chan*) ; 

__attribute__((used)) static inline int l2cap_disconnect_rsp(struct l2cap_conn *conn,
				       struct l2cap_cmd_hdr *cmd, u16 cmd_len,
				       u8 *data)
{
	struct l2cap_disconn_rsp *rsp = (struct l2cap_disconn_rsp *) data;
	u16 dcid, scid;
	struct l2cap_chan *chan;

	if (cmd_len != sizeof(*rsp))
		return -EPROTO;

	scid = __le16_to_cpu(rsp->scid);
	dcid = __le16_to_cpu(rsp->dcid);

	BT_DBG("dcid 0x%4.4x scid 0x%4.4x", dcid, scid);

	mutex_lock(&conn->chan_lock);

	chan = __l2cap_get_chan_by_scid(conn, scid);
	if (!chan) {
		mutex_unlock(&conn->chan_lock);
		return 0;
	}

	l2cap_chan_lock(chan);

	if (chan->state != BT_DISCONN) {
		l2cap_chan_unlock(chan);
		mutex_unlock(&conn->chan_lock);
		return 0;
	}

	l2cap_chan_hold(chan);
	l2cap_chan_del(chan, 0);

	l2cap_chan_unlock(chan);

	chan->ops->close(chan);
	l2cap_chan_put(chan);

	mutex_unlock(&conn->chan_lock);

	return 0;
}