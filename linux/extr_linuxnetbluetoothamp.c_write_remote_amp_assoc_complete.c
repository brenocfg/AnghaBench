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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct hci_rp_write_remote_amp_assoc {int /*<<< orphan*/  phy_handle; scalar_t__ status; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amp_write_rem_assoc_continue (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_remote_amp_assoc_complete(struct hci_dev *hdev, u8 status,
					    u16 opcode, struct sk_buff *skb)
{
	struct hci_rp_write_remote_amp_assoc *rp = (void *)skb->data;

	BT_DBG("%s status 0x%2.2x phy_handle 0x%2.2x",
	       hdev->name, rp->status, rp->phy_handle);

	if (rp->status)
		return;

	amp_write_rem_assoc_continue(hdev, rp->phy_handle);
}