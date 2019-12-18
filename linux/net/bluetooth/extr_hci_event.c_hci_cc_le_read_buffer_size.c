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
struct hci_rp_le_read_buffer_size {int /*<<< orphan*/  le_max_pkt; int /*<<< orphan*/  le_mtu; scalar_t__ status; } ;
struct hci_dev {int /*<<< orphan*/  le_pkts; int /*<<< orphan*/  le_mtu; int /*<<< orphan*/  name; int /*<<< orphan*/  le_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_le_read_buffer_size(struct hci_dev *hdev,
				       struct sk_buff *skb)
{
	struct hci_rp_le_read_buffer_size *rp = (void *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	if (rp->status)
		return;

	hdev->le_mtu = __le16_to_cpu(rp->le_mtu);
	hdev->le_pkts = rp->le_max_pkt;

	hdev->le_cnt = hdev->le_pkts;

	BT_DBG("%s le mtu %d:%d", hdev->name, hdev->le_mtu, hdev->le_pkts);
}