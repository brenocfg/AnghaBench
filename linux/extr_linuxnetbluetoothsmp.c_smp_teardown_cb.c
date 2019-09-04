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
struct l2cap_conn {int /*<<< orphan*/ * smp; } ;
struct l2cap_chan {scalar_t__ data; struct l2cap_conn* conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_put (struct l2cap_chan*) ; 
 int /*<<< orphan*/  smp_chan_destroy (struct l2cap_conn*) ; 

__attribute__((used)) static void smp_teardown_cb(struct l2cap_chan *chan, int err)
{
	struct l2cap_conn *conn = chan->conn;

	BT_DBG("chan %p", chan);

	if (chan->data)
		smp_chan_destroy(conn);

	conn->smp = NULL;
	l2cap_chan_put(chan);
}