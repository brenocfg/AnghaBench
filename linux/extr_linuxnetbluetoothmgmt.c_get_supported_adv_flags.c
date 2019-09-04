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
struct hci_dev {scalar_t__ adv_tx_power; int* le_features; } ;

/* Variables and functions */
 int HCI_LE_PHY_2M ; 
 int HCI_LE_PHY_CODED ; 
 scalar_t__ HCI_TX_POWER_INVALID ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_APPEARANCE ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_CONNECTABLE ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_DISCOV ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_LIMITED_DISCOV ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_LOCAL_NAME ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_MANAGED_FLAGS ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_SEC_1M ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_SEC_2M ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_SEC_CODED ; 
 int /*<<< orphan*/  MGMT_ADV_FLAG_TX_POWER ; 
 scalar_t__ ext_adv_capable (struct hci_dev*) ; 

__attribute__((used)) static u32 get_supported_adv_flags(struct hci_dev *hdev)
{
	u32 flags = 0;

	flags |= MGMT_ADV_FLAG_CONNECTABLE;
	flags |= MGMT_ADV_FLAG_DISCOV;
	flags |= MGMT_ADV_FLAG_LIMITED_DISCOV;
	flags |= MGMT_ADV_FLAG_MANAGED_FLAGS;
	flags |= MGMT_ADV_FLAG_APPEARANCE;
	flags |= MGMT_ADV_FLAG_LOCAL_NAME;

	/* In extended adv TX_POWER returned from Set Adv Param
	 * will be always valid.
	 */
	if ((hdev->adv_tx_power != HCI_TX_POWER_INVALID) ||
	    ext_adv_capable(hdev))
		flags |= MGMT_ADV_FLAG_TX_POWER;

	if (ext_adv_capable(hdev)) {
		flags |= MGMT_ADV_FLAG_SEC_1M;

		if (hdev->le_features[1] & HCI_LE_PHY_2M)
			flags |= MGMT_ADV_FLAG_SEC_2M;

		if (hdev->le_features[1] & HCI_LE_PHY_CODED)
			flags |= MGMT_ADV_FLAG_SEC_CODED;
	}

	return flags;
}