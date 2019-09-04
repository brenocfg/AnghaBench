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
typedef  int u32 ;
struct hci_dev {scalar_t__ adv_tx_power; } ;
struct adv_info {scalar_t__ tx_power; scalar_t__ adv_data_len; int /*<<< orphan*/  adv_data; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int EIR_FLAGS ; 
 int EIR_TX_POWER ; 
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 scalar_t__ HCI_TX_POWER_INVALID ; 
 int LE_AD_GENERAL ; 
 int LE_AD_LIMITED ; 
 int LE_AD_NO_BREDR ; 
 int MGMT_ADV_FLAG_DISCOV ; 
 int MGMT_ADV_FLAG_LIMITED_DISCOV ; 
 int MGMT_ADV_FLAG_MANAGED_FLAGS ; 
 int MGMT_ADV_FLAG_TX_POWER ; 
 scalar_t__ ext_adv_capable (struct hci_dev*) ; 
 int get_adv_instance_flags (struct hci_dev*,int) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct adv_info* hci_find_adv_instance (struct hci_dev*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int mgmt_get_adv_discov_flags (struct hci_dev*) ; 

__attribute__((used)) static u8 create_instance_adv_data(struct hci_dev *hdev, u8 instance, u8 *ptr)
{
	struct adv_info *adv_instance = NULL;
	u8 ad_len = 0, flags = 0;
	u32 instance_flags;

	/* Return 0 when the current instance identifier is invalid. */
	if (instance) {
		adv_instance = hci_find_adv_instance(hdev, instance);
		if (!adv_instance)
			return 0;
	}

	instance_flags = get_adv_instance_flags(hdev, instance);

	/* The Add Advertising command allows userspace to set both the general
	 * and limited discoverable flags.
	 */
	if (instance_flags & MGMT_ADV_FLAG_DISCOV)
		flags |= LE_AD_GENERAL;

	if (instance_flags & MGMT_ADV_FLAG_LIMITED_DISCOV)
		flags |= LE_AD_LIMITED;

	if (!hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		flags |= LE_AD_NO_BREDR;

	if (flags || (instance_flags & MGMT_ADV_FLAG_MANAGED_FLAGS)) {
		/* If a discovery flag wasn't provided, simply use the global
		 * settings.
		 */
		if (!flags)
			flags |= mgmt_get_adv_discov_flags(hdev);

		/* If flags would still be empty, then there is no need to
		 * include the "Flags" AD field".
		 */
		if (flags) {
			ptr[0] = 0x02;
			ptr[1] = EIR_FLAGS;
			ptr[2] = flags;

			ad_len += 3;
			ptr += 3;
		}
	}

	if (adv_instance) {
		memcpy(ptr, adv_instance->adv_data,
		       adv_instance->adv_data_len);
		ad_len += adv_instance->adv_data_len;
		ptr += adv_instance->adv_data_len;
	}

	if (instance_flags & MGMT_ADV_FLAG_TX_POWER) {
		s8 adv_tx_power;

		if (ext_adv_capable(hdev)) {
			if (adv_instance)
				adv_tx_power = adv_instance->tx_power;
			else
				adv_tx_power = hdev->adv_tx_power;
		} else {
			adv_tx_power = hdev->adv_tx_power;
		}

		/* Provide Tx Power only if we can provide a valid value for it */
		if (adv_tx_power != HCI_TX_POWER_INVALID) {
			ptr[0] = 0x02;
			ptr[1] = EIR_TX_POWER;
			ptr[2] = (u8)adv_tx_power;

			ad_len += 3;
			ptr += 3;
		}
	}

	return ad_len;
}