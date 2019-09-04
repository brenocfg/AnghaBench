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
struct hci_rp_read_local_amp_info {int /*<<< orphan*/  max_flush_to; int /*<<< orphan*/  be_flush_to; int /*<<< orphan*/  max_assoc_size; int /*<<< orphan*/  pal_cap; int /*<<< orphan*/  amp_type; int /*<<< orphan*/  max_pdu; int /*<<< orphan*/  min_latency; int /*<<< orphan*/  max_bw; int /*<<< orphan*/  total_bw; int /*<<< orphan*/  amp_status; scalar_t__ status; } ;
struct hci_dev {void* amp_max_flush_to; void* amp_be_flush_to; void* amp_assoc_size; void* amp_pal_cap; int /*<<< orphan*/  amp_type; void* amp_max_pdu; void* amp_min_latency; void* amp_max_bw; void* amp_total_bw; int /*<<< orphan*/  amp_status; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 void* __le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* __le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_read_local_amp_info(struct hci_dev *hdev,
				       struct sk_buff *skb)
{
	struct hci_rp_read_local_amp_info *rp = (void *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	if (rp->status)
		return;

	hdev->amp_status = rp->amp_status;
	hdev->amp_total_bw = __le32_to_cpu(rp->total_bw);
	hdev->amp_max_bw = __le32_to_cpu(rp->max_bw);
	hdev->amp_min_latency = __le32_to_cpu(rp->min_latency);
	hdev->amp_max_pdu = __le32_to_cpu(rp->max_pdu);
	hdev->amp_type = rp->amp_type;
	hdev->amp_pal_cap = __le16_to_cpu(rp->pal_cap);
	hdev->amp_assoc_size = __le16_to_cpu(rp->max_assoc_size);
	hdev->amp_be_flush_to = __le32_to_cpu(rp->be_flush_to);
	hdev->amp_max_flush_to = __le32_to_cpu(rp->max_flush_to);
}