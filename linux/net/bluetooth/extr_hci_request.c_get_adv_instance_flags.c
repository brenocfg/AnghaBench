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
struct hci_dev {int dummy; } ;
struct adv_info {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_ADVERTISING_CONNECTABLE ; 
 int /*<<< orphan*/  HCI_DISCOVERABLE ; 
 int /*<<< orphan*/  HCI_LIMITED_DISCOVERABLE ; 
 int MGMT_ADV_FLAG_CONNECTABLE ; 
 int MGMT_ADV_FLAG_DISCOV ; 
 int MGMT_ADV_FLAG_LIMITED_DISCOV ; 
 int MGMT_ADV_FLAG_MANAGED_FLAGS ; 
 int MGMT_ADV_FLAG_TX_POWER ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 struct adv_info* hci_find_adv_instance (struct hci_dev*,int) ; 

__attribute__((used)) static u32 get_adv_instance_flags(struct hci_dev *hdev, u8 instance)
{
	u32 flags;
	struct adv_info *adv_instance;

	if (instance == 0x00) {
		/* Instance 0 always manages the "Tx Power" and "Flags"
		 * fields
		 */
		flags = MGMT_ADV_FLAG_TX_POWER | MGMT_ADV_FLAG_MANAGED_FLAGS;

		/* For instance 0, the HCI_ADVERTISING_CONNECTABLE setting
		 * corresponds to the "connectable" instance flag.
		 */
		if (hci_dev_test_flag(hdev, HCI_ADVERTISING_CONNECTABLE))
			flags |= MGMT_ADV_FLAG_CONNECTABLE;

		if (hci_dev_test_flag(hdev, HCI_LIMITED_DISCOVERABLE))
			flags |= MGMT_ADV_FLAG_LIMITED_DISCOV;
		else if (hci_dev_test_flag(hdev, HCI_DISCOVERABLE))
			flags |= MGMT_ADV_FLAG_DISCOV;

		return flags;
	}

	adv_instance = hci_find_adv_instance(hdev, instance);

	/* Return 0 when we got an invalid instance identifier. */
	if (!adv_instance)
		return 0;

	return adv_instance->flags;
}