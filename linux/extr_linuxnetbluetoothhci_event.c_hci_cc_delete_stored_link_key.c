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
struct hci_rp_delete_stored_link_key {scalar_t__ num_keys; scalar_t__ status; } ;
struct hci_dev {scalar_t__ stored_num_keys; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void hci_cc_delete_stored_link_key(struct hci_dev *hdev,
					  struct sk_buff *skb)
{
	struct hci_rp_delete_stored_link_key *rp = (void *)skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);

	if (rp->status)
		return;

	if (rp->num_keys <= hdev->stored_num_keys)
		hdev->stored_num_keys -= rp->num_keys;
	else
		hdev->stored_num_keys = 0;
}