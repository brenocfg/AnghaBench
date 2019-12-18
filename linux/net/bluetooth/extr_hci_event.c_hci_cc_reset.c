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
struct hci_dev {int /*<<< orphan*/  le_resolv_list; int /*<<< orphan*/  le_white_list; scalar_t__ ssp_debug_mode; int /*<<< orphan*/  le_scan_type; scalar_t__ scan_rsp_data_len; int /*<<< orphan*/  scan_rsp_data; scalar_t__ adv_data_len; int /*<<< orphan*/  adv_data; void* adv_tx_power; void* inq_tx_power; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DISCOVERY_STOPPED ; 
 int /*<<< orphan*/  HCI_RESET ; 
 void* HCI_TX_POWER_INVALID ; 
 int /*<<< orphan*/  LE_SCAN_PASSIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_bdaddr_list_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_clear_volatile_flags (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_discovery_set_state (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hci_cc_reset(struct hci_dev *hdev, struct sk_buff *skb)
{
	__u8 status = *((__u8 *) skb->data);

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	clear_bit(HCI_RESET, &hdev->flags);

	if (status)
		return;

	/* Reset all non-persistent flags */
	hci_dev_clear_volatile_flags(hdev);

	hci_discovery_set_state(hdev, DISCOVERY_STOPPED);

	hdev->inq_tx_power = HCI_TX_POWER_INVALID;
	hdev->adv_tx_power = HCI_TX_POWER_INVALID;

	memset(hdev->adv_data, 0, sizeof(hdev->adv_data));
	hdev->adv_data_len = 0;

	memset(hdev->scan_rsp_data, 0, sizeof(hdev->scan_rsp_data));
	hdev->scan_rsp_data_len = 0;

	hdev->le_scan_type = LE_SCAN_PASSIVE;

	hdev->ssp_debug_mode = 0;

	hci_bdaddr_list_clear(&hdev->le_white_list);
	hci_bdaddr_list_clear(&hdev->le_resolv_list);
}