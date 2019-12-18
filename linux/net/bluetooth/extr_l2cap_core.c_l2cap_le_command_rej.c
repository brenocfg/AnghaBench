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
struct l2cap_conn {int /*<<< orphan*/  chan_lock; } ;
struct l2cap_cmd_rej_unk {int dummy; } ;
struct l2cap_cmd_hdr {int /*<<< orphan*/  ident; } ;
struct l2cap_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNREFUSED ; 
 int EPROTO ; 
 struct l2cap_chan* __l2cap_get_chan_by_ident (struct l2cap_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_del (struct l2cap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int l2cap_le_command_rej(struct l2cap_conn *conn,
				       struct l2cap_cmd_hdr *cmd, u16 cmd_len,
				       u8 *data)
{
	struct l2cap_cmd_rej_unk *rej = (struct l2cap_cmd_rej_unk *) data;
	struct l2cap_chan *chan;

	if (cmd_len < sizeof(*rej))
		return -EPROTO;

	mutex_lock(&conn->chan_lock);

	chan = __l2cap_get_chan_by_ident(conn, cmd->ident);
	if (!chan)
		goto done;

	l2cap_chan_lock(chan);
	l2cap_chan_del(chan, ECONNREFUSED);
	l2cap_chan_unlock(chan);

done:
	mutex_unlock(&conn->chan_lock);
	return 0;
}