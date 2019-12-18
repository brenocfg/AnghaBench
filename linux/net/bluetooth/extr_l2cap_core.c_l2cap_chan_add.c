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
struct l2cap_conn {int /*<<< orphan*/  chan_lock; } ;
struct l2cap_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __l2cap_chan_add (struct l2cap_conn*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void l2cap_chan_add(struct l2cap_conn *conn, struct l2cap_chan *chan)
{
	mutex_lock(&conn->chan_lock);
	__l2cap_chan_add(conn, chan);
	mutex_unlock(&conn->chan_lock);
}