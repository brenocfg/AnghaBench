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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct hci_dev {scalar_t__ adv_instance_cnt; scalar_t__ le_num_of_adv_sets; int /*<<< orphan*/  name; int /*<<< orphan*/  adv_instances; } ;
struct adv_info {int pending; int instance; int /*<<< orphan*/  rpa_expired_cb; int /*<<< orphan*/  tx_power; scalar_t__ duration; scalar_t__ remaining_time; scalar_t__ timeout; int /*<<< orphan*/  scan_rsp_data; int /*<<< orphan*/  adv_data; scalar_t__ scan_rsp_len; scalar_t__ adv_data_len; int /*<<< orphan*/  flags; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HCI_DEFAULT_ADV_DURATION ; 
 int HCI_MAX_ADV_INSTANCES ; 
 int /*<<< orphan*/  HCI_TX_POWER_INVALID ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv_instance_rpa_expired ; 
 struct adv_info* hci_find_adv_instance (struct hci_dev*,int) ; 
 struct adv_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int hci_add_adv_instance(struct hci_dev *hdev, u8 instance, u32 flags,
			 u16 adv_data_len, u8 *adv_data,
			 u16 scan_rsp_len, u8 *scan_rsp_data,
			 u16 timeout, u16 duration)
{
	struct adv_info *adv_instance;

	adv_instance = hci_find_adv_instance(hdev, instance);
	if (adv_instance) {
		memset(adv_instance->adv_data, 0,
		       sizeof(adv_instance->adv_data));
		memset(adv_instance->scan_rsp_data, 0,
		       sizeof(adv_instance->scan_rsp_data));
	} else {
		if (hdev->adv_instance_cnt >= hdev->le_num_of_adv_sets ||
		    instance < 1 || instance > HCI_MAX_ADV_INSTANCES)
			return -EOVERFLOW;

		adv_instance = kzalloc(sizeof(*adv_instance), GFP_KERNEL);
		if (!adv_instance)
			return -ENOMEM;

		adv_instance->pending = true;
		adv_instance->instance = instance;
		list_add(&adv_instance->list, &hdev->adv_instances);
		hdev->adv_instance_cnt++;
	}

	adv_instance->flags = flags;
	adv_instance->adv_data_len = adv_data_len;
	adv_instance->scan_rsp_len = scan_rsp_len;

	if (adv_data_len)
		memcpy(adv_instance->adv_data, adv_data, adv_data_len);

	if (scan_rsp_len)
		memcpy(adv_instance->scan_rsp_data,
		       scan_rsp_data, scan_rsp_len);

	adv_instance->timeout = timeout;
	adv_instance->remaining_time = timeout;

	if (duration == 0)
		adv_instance->duration = HCI_DEFAULT_ADV_DURATION;
	else
		adv_instance->duration = duration;

	adv_instance->tx_power = HCI_TX_POWER_INVALID;

	INIT_DELAYED_WORK(&adv_instance->rpa_expired_cb,
			  adv_instance_rpa_expired);

	BT_DBG("%s for %dMR", hdev->name, instance);

	return 0;
}