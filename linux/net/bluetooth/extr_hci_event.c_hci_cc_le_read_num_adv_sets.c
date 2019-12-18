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
struct hci_rp_le_read_num_supported_adv_sets {int /*<<< orphan*/  num_of_sets; scalar_t__ status; } ;
struct hci_dev {int /*<<< orphan*/  le_num_of_adv_sets; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_le_read_num_adv_sets(struct hci_dev *hdev,
				      struct sk_buff *skb)
{
	struct hci_rp_le_read_num_supported_adv_sets *rp = (void *) skb->data;

	BT_DBG("%s status 0x%2.2x No of Adv sets %u", hdev->name, rp->status,
	       rp->num_of_sets);

	if (rp->status)
		return;

	hdev->le_num_of_adv_sets = rp->num_of_sets;
}