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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  priority; } ;
struct l2cap_conn {int /*<<< orphan*/  hchan; TYPE_1__* hcon; } ;
struct TYPE_4__ {int /*<<< orphan*/  force_active; } ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_START ; 
 int /*<<< orphan*/  ACL_START_NO_FLUSH ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_POWER_FORCE_ACTIVE_ON ; 
 int /*<<< orphan*/  HCI_PRIO_MAX ; 
 scalar_t__ LE_LINK ; 
 TYPE_2__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  hci_send_acl (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* l2cap_build_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ lmp_no_flush_capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2cap_send_cmd(struct l2cap_conn *conn, u8 ident, u8 code, u16 len,
			   void *data)
{
	struct sk_buff *skb = l2cap_build_cmd(conn, code, ident, len, data);
	u8 flags;

	BT_DBG("code 0x%2.2x", code);

	if (!skb)
		return;

	/* Use NO_FLUSH if supported or we have an LE link (which does
	 * not support auto-flushing packets) */
	if (lmp_no_flush_capable(conn->hcon->hdev) ||
	    conn->hcon->type == LE_LINK)
		flags = ACL_START_NO_FLUSH;
	else
		flags = ACL_START;

	bt_cb(skb)->force_active = BT_POWER_FORCE_ACTIVE_ON;
	skb->priority = HCI_PRIO_MAX;

	hci_send_acl(conn->hchan, skb, flags);
}