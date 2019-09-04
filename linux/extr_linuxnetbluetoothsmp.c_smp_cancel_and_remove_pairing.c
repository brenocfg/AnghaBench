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
struct smp_chan {int /*<<< orphan*/  flags; int /*<<< orphan*/ * remote_irk; int /*<<< orphan*/ * slave_ltk; int /*<<< orphan*/ * ltk; } ;
struct l2cap_conn {struct l2cap_chan* smp; } ;
struct l2cap_chan {struct smp_chan* data; } ;
struct hci_dev {int dummy; } ;
struct hci_conn {struct l2cap_conn* l2cap_data; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMP_FLAG_COMPLETE ; 
 int /*<<< orphan*/  SMP_UNSPECIFIED ; 
 struct hci_conn* hci_conn_hash_lookup_le (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_remove_irk (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hci_remove_ltk (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_chan_lock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_chan_unlock (struct l2cap_chan*) ; 
 int /*<<< orphan*/  smp_failure (struct l2cap_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int smp_cancel_and_remove_pairing(struct hci_dev *hdev, bdaddr_t *bdaddr,
				  u8 addr_type)
{
	struct hci_conn *hcon;
	struct l2cap_conn *conn;
	struct l2cap_chan *chan;
	struct smp_chan *smp;
	int err;

	err = hci_remove_ltk(hdev, bdaddr, addr_type);
	hci_remove_irk(hdev, bdaddr, addr_type);

	hcon = hci_conn_hash_lookup_le(hdev, bdaddr, addr_type);
	if (!hcon)
		goto done;

	conn = hcon->l2cap_data;
	if (!conn)
		goto done;

	chan = conn->smp;
	if (!chan)
		goto done;

	l2cap_chan_lock(chan);

	smp = chan->data;
	if (smp) {
		/* Set keys to NULL to make sure smp_failure() does not try to
		 * remove and free already invalidated rcu list entries. */
		smp->ltk = NULL;
		smp->slave_ltk = NULL;
		smp->remote_irk = NULL;

		if (test_bit(SMP_FLAG_COMPLETE, &smp->flags))
			smp_failure(conn, 0);
		else
			smp_failure(conn, SMP_UNSPECIFIED);
		err = 0;
	}

	l2cap_chan_unlock(chan);

done:
	return err;
}