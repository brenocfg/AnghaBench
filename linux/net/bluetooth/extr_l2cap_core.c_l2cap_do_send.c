#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  priority; int /*<<< orphan*/  len; } ;
struct l2cap_chan {TYPE_1__* conn; int /*<<< orphan*/  flags; scalar_t__ hs_hchan; scalar_t__ hs_hcon; } ;
struct hci_conn {scalar_t__ type; int /*<<< orphan*/  hdev; } ;
struct TYPE_4__ {scalar_t__ force_active; } ;
struct TYPE_3__ {scalar_t__ hchan; struct hci_conn* hcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_COMPLETE ; 
 int /*<<< orphan*/  ACL_START ; 
 int /*<<< orphan*/  ACL_START_NO_FLUSH ; 
 int /*<<< orphan*/  BT_DBG (char*,struct l2cap_chan*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAG_FLUSHABLE ; 
 int /*<<< orphan*/  FLAG_FORCE_ACTIVE ; 
 scalar_t__ LE_LINK ; 
 int /*<<< orphan*/  __chan_is_moving (struct l2cap_chan*) ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  hci_send_acl (scalar_t__,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ lmp_no_flush_capable (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2cap_do_send(struct l2cap_chan *chan, struct sk_buff *skb)
{
	struct hci_conn *hcon = chan->conn->hcon;
	u16 flags;

	BT_DBG("chan %p, skb %p len %d priority %u", chan, skb, skb->len,
	       skb->priority);

	if (chan->hs_hcon && !__chan_is_moving(chan)) {
		if (chan->hs_hchan)
			hci_send_acl(chan->hs_hchan, skb, ACL_COMPLETE);
		else
			kfree_skb(skb);

		return;
	}

	/* Use NO_FLUSH for LE links (where this is the only option) or
	 * if the BR/EDR link supports it and flushing has not been
	 * explicitly requested (through FLAG_FLUSHABLE).
	 */
	if (hcon->type == LE_LINK ||
	    (!test_bit(FLAG_FLUSHABLE, &chan->flags) &&
	     lmp_no_flush_capable(hcon->hdev)))
		flags = ACL_START_NO_FLUSH;
	else
		flags = ACL_START;

	bt_cb(skb)->force_active = test_bit(FLAG_FORCE_ACTIVE, &chan->flags);
	hci_send_acl(chan->conn->hchan, skb, flags);
}