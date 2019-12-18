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
typedef  int /*<<< orphan*/  u16 ;
struct l2cap_conn {int /*<<< orphan*/  chan_lock; } ;
struct l2cap_chan {int dummy; } ;

/* Variables and functions */
 struct l2cap_chan* __l2cap_get_chan_by_scid (struct l2cap_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct l2cap_chan *l2cap_get_chan_by_scid(struct l2cap_conn *conn,
						 u16 cid)
{
	struct l2cap_chan *c;

	mutex_lock(&conn->chan_lock);
	c = __l2cap_get_chan_by_scid(conn, cid);
	if (c)
		l2cap_chan_lock(c);
	mutex_unlock(&conn->chan_lock);

	return c;
}