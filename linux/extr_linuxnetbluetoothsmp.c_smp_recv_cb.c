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
struct smp_chan {int /*<<< orphan*/  security_timer; } ;
struct sk_buff {int dummy; } ;
struct l2cap_chan {TYPE_1__* conn; struct smp_chan* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  hcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*) ; 
 int /*<<< orphan*/  HCI_ERROR_AUTH_FAILURE ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smp_sig_channel (struct l2cap_chan*,struct sk_buff*) ; 

__attribute__((used)) static int smp_recv_cb(struct l2cap_chan *chan, struct sk_buff *skb)
{
	int err;

	BT_DBG("chan %p", chan);

	err = smp_sig_channel(chan, skb);
	if (err) {
		struct smp_chan *smp = chan->data;

		if (smp)
			cancel_delayed_work_sync(&smp->security_timer);

		hci_disconnect(chan->conn->hcon, HCI_ERROR_AUTH_FAILURE);
	}

	return err;
}