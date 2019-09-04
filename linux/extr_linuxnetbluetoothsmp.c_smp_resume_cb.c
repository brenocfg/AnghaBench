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
struct smp_chan {int /*<<< orphan*/  security_timer; } ;
struct l2cap_conn {struct hci_conn* hcon; } ;
struct l2cap_chan {struct l2cap_conn* conn; struct smp_chan* data; } ;
struct hci_conn {scalar_t__ type; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT ; 
 int /*<<< orphan*/  bredr_pairing (struct l2cap_chan*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_distribute_keys (struct smp_chan*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smp_resume_cb(struct l2cap_chan *chan)
{
	struct smp_chan *smp = chan->data;
	struct l2cap_conn *conn = chan->conn;
	struct hci_conn *hcon = conn->hcon;

	BT_DBG("chan %p", chan);

	if (hcon->type == ACL_LINK) {
		bredr_pairing(chan);
		return;
	}

	if (!smp)
		return;

	if (!test_bit(HCI_CONN_ENCRYPT, &hcon->flags))
		return;

	cancel_delayed_work(&smp->security_timer);

	smp_distribute_keys(smp);
}