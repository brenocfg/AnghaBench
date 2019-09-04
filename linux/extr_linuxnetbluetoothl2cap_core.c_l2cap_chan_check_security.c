#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct l2cap_conn {TYPE_1__* hcon; } ;
struct l2cap_chan {int /*<<< orphan*/  sec_level; struct l2cap_conn* conn; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ LE_LINK ; 
 int hci_conn_security (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l2cap_get_auth_type (struct l2cap_chan*) ; 
 int smp_conn_security (TYPE_1__*,int /*<<< orphan*/ ) ; 

int l2cap_chan_check_security(struct l2cap_chan *chan, bool initiator)
{
	struct l2cap_conn *conn = chan->conn;
	__u8 auth_type;

	if (conn->hcon->type == LE_LINK)
		return smp_conn_security(conn->hcon, chan->sec_level);

	auth_type = l2cap_get_auth_type(chan);

	return hci_conn_security(conn->hcon, chan->sec_level, auth_type,
				 initiator);
}