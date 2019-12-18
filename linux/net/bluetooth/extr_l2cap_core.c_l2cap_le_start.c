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
struct l2cap_conn {int /*<<< orphan*/  hcon; } ;
struct l2cap_chan {scalar_t__ state; int /*<<< orphan*/  psm; int /*<<< orphan*/  sec_level; struct l2cap_conn* conn; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECT ; 
 int /*<<< orphan*/  l2cap_chan_ready (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_le_connect (struct l2cap_chan*) ; 
 int /*<<< orphan*/  smp_conn_security (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_le_start(struct l2cap_chan *chan)
{
	struct l2cap_conn *conn = chan->conn;

	if (!smp_conn_security(conn->hcon, chan->sec_level))
		return;

	if (!chan->psm) {
		l2cap_chan_ready(chan);
		return;
	}

	if (chan->state == BT_CONNECT)
		l2cap_le_connect(chan);
}