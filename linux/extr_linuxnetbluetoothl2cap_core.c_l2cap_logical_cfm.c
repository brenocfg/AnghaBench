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
typedef  scalar_t__ u8 ;
struct l2cap_chan {scalar_t__ state; scalar_t__ local_amp_id; } ;
struct hci_chan {int dummy; } ;

/* Variables and functions */
 scalar_t__ AMP_ID_BREDR ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,struct hci_chan*,scalar_t__) ; 
 int /*<<< orphan*/  __release_logical_link (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_logical_fail (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_logical_finish_create (struct l2cap_chan*,struct hci_chan*) ; 
 int /*<<< orphan*/  l2cap_logical_finish_move (struct l2cap_chan*,struct hci_chan*) ; 

void l2cap_logical_cfm(struct l2cap_chan *chan, struct hci_chan *hchan,
		       u8 status)
{
	BT_DBG("chan %p, hchan %p, status %d", chan, hchan, status);

	if (status) {
		l2cap_logical_fail(chan);
		__release_logical_link(chan);
		return;
	}

	if (chan->state != BT_CONNECTED) {
		/* Ignore logical link if channel is on BR/EDR */
		if (chan->local_amp_id != AMP_ID_BREDR)
			l2cap_logical_finish_create(chan, hchan);
	} else {
		l2cap_logical_finish_move(chan, hchan);
	}
}