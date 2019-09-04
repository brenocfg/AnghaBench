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
struct l2cap_conn {struct l2cap_chan* smp; struct hci_conn* hcon; } ;
struct l2cap_chan {struct l2cap_conn* conn; } ;
struct hci_conn {scalar_t__ type; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT ; 
 int /*<<< orphan*/  bredr_pairing (struct l2cap_chan*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smp_ready_cb(struct l2cap_chan *chan)
{
	struct l2cap_conn *conn = chan->conn;
	struct hci_conn *hcon = conn->hcon;

	BT_DBG("chan %p", chan);

	/* No need to call l2cap_chan_hold() here since we already own
	 * the reference taken in smp_new_conn_cb(). This is just the
	 * first time that we tie it to a specific pointer. The code in
	 * l2cap_core.c ensures that there's no risk this function wont
	 * get called if smp_new_conn_cb was previously called.
	 */
	conn->smp = chan;

	if (hcon->type == ACL_LINK && test_bit(HCI_CONN_ENCRYPT, &hcon->flags))
		bredr_pairing(chan);
}