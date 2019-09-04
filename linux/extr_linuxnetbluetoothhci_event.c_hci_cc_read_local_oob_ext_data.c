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
struct hci_rp_read_local_oob_ext_data {int /*<<< orphan*/  status; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cc_read_local_oob_ext_data(struct hci_dev *hdev,
					   struct sk_buff *skb)
{
	struct hci_rp_read_local_oob_ext_data *rp = (void *) skb->data;

	BT_DBG("%s status 0x%2.2x", hdev->name, rp->status);
}