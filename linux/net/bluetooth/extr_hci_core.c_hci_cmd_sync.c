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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETDOWN ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_UP ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_dbg (struct hci_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_sync_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_sync_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct sk_buff *hci_cmd_sync(struct hci_dev *hdev, u16 opcode, u32 plen,
			     const void *param, u32 timeout)
{
	struct sk_buff *skb;

	if (!test_bit(HCI_UP, &hdev->flags))
		return ERR_PTR(-ENETDOWN);

	bt_dev_dbg(hdev, "opcode 0x%4.4x plen %d", opcode, plen);

	hci_req_sync_lock(hdev);
	skb = __hci_cmd_sync(hdev, opcode, plen, param, timeout);
	hci_req_sync_unlock(hdev);

	return skb;
}