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
struct sk_buff {scalar_t__ data; } ;
struct inquiry_data {int pscan_mode; int ssp_mode; int /*<<< orphan*/  rssi; int /*<<< orphan*/  clock_offset; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  pscan_period_mode; int /*<<< orphan*/  pscan_rep_mode; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct extended_inquiry_info {int /*<<< orphan*/  data; int /*<<< orphan*/  rssi; int /*<<< orphan*/  dev_class; int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  clock_offset; int /*<<< orphan*/  pscan_period_mode; int /*<<< orphan*/  pscan_rep_mode; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EIR_NAME_COMPLETE ; 
 int /*<<< orphan*/  HCI_MGMT ; 
 int /*<<< orphan*/  HCI_PERIODIC_INQ ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int eir_get_data (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t eir_get_length (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_inquiry_cache_update (struct hci_dev*,struct inquiry_data*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmt_device_found (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_extended_inquiry_result_evt(struct hci_dev *hdev,
					    struct sk_buff *skb)
{
	struct inquiry_data data;
	struct extended_inquiry_info *info = (void *) (skb->data + 1);
	int num_rsp = *((__u8 *) skb->data);
	size_t eir_len;

	BT_DBG("%s num_rsp %d", hdev->name, num_rsp);

	if (!num_rsp)
		return;

	if (hci_dev_test_flag(hdev, HCI_PERIODIC_INQ))
		return;

	hci_dev_lock(hdev);

	for (; num_rsp; num_rsp--, info++) {
		u32 flags;
		bool name_known;

		bacpy(&data.bdaddr, &info->bdaddr);
		data.pscan_rep_mode	= info->pscan_rep_mode;
		data.pscan_period_mode	= info->pscan_period_mode;
		data.pscan_mode		= 0x00;
		memcpy(data.dev_class, info->dev_class, 3);
		data.clock_offset	= info->clock_offset;
		data.rssi		= info->rssi;
		data.ssp_mode		= 0x01;

		if (hci_dev_test_flag(hdev, HCI_MGMT))
			name_known = eir_get_data(info->data,
						  sizeof(info->data),
						  EIR_NAME_COMPLETE, NULL);
		else
			name_known = true;

		flags = hci_inquiry_cache_update(hdev, &data, name_known);

		eir_len = eir_get_length(info->data, sizeof(info->data));

		mgmt_device_found(hdev, &info->bdaddr, ACL_LINK, 0x00,
				  info->dev_class, info->rssi,
				  flags, info->data, eir_len, NULL, 0);
	}

	hci_dev_unlock(hdev);
}