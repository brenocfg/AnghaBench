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
struct sk_buff {scalar_t__ data; } ;
struct hci_rp_read_inq_rsp_tx_power {int /*<<< orphan*/  tx_power; scalar_t__ status; } ;
struct hci_dev {int /*<<< orphan*/  inq_tx_power; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hci_cc_read_inq_rsp_tx_power(struct hci_dev *hdev,
					 struct sk_buff *skb)
{
	struct hci_rp_read_inq_rsp_tx_power *rp = (void *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	if (rp->status)
		return;

	hdev->inq_tx_power = rp->tx_power;
}