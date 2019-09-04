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
struct hci_dev {int /*<<< orphan*/  static_addr; int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 int /*<<< orphan*/  HCI_ADVERTISING ; 
 int /*<<< orphan*/  HCI_BONDABLE ; 
 int /*<<< orphan*/  HCI_BREDR_ENABLED ; 
 int /*<<< orphan*/  HCI_CONNECTABLE ; 
 int /*<<< orphan*/  HCI_DISCOVERABLE ; 
 int /*<<< orphan*/  HCI_FAST_CONNECTABLE ; 
 int /*<<< orphan*/  HCI_FORCE_STATIC_ADDR ; 
 int /*<<< orphan*/  HCI_HS_ENABLED ; 
 int /*<<< orphan*/  HCI_KEEP_DEBUG_KEYS ; 
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  HCI_LINK_SECURITY ; 
 int /*<<< orphan*/  HCI_PRIVACY ; 
 int /*<<< orphan*/  HCI_SC_ENABLED ; 
 int /*<<< orphan*/  HCI_SSP_ENABLED ; 
 int /*<<< orphan*/  MGMT_SETTING_ADVERTISING ; 
 int /*<<< orphan*/  MGMT_SETTING_BONDABLE ; 
 int /*<<< orphan*/  MGMT_SETTING_BREDR ; 
 int /*<<< orphan*/  MGMT_SETTING_CONNECTABLE ; 
 int /*<<< orphan*/  MGMT_SETTING_DEBUG_KEYS ; 
 int /*<<< orphan*/  MGMT_SETTING_DISCOVERABLE ; 
 int /*<<< orphan*/  MGMT_SETTING_FAST_CONNECTABLE ; 
 int /*<<< orphan*/  MGMT_SETTING_HS ; 
 int /*<<< orphan*/  MGMT_SETTING_LE ; 
 int /*<<< orphan*/  MGMT_SETTING_LINK_SECURITY ; 
 int /*<<< orphan*/  MGMT_SETTING_POWERED ; 
 int /*<<< orphan*/  MGMT_SETTING_PRIVACY ; 
 int /*<<< orphan*/  MGMT_SETTING_SECURE_CONN ; 
 int /*<<< orphan*/  MGMT_SETTING_SSP ; 
 int /*<<< orphan*/  MGMT_SETTING_STATIC_ADDRESS ; 
 scalar_t__ bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ hdev_is_powered (struct hci_dev*) ; 

__attribute__((used)) static u32 get_current_settings(struct hci_dev *hdev)
{
	u32 settings = 0;

	if (hdev_is_powered(hdev))
		settings |= MGMT_SETTING_POWERED;

	if (hci_dev_test_flag(hdev, HCI_CONNECTABLE))
		settings |= MGMT_SETTING_CONNECTABLE;

	if (hci_dev_test_flag(hdev, HCI_FAST_CONNECTABLE))
		settings |= MGMT_SETTING_FAST_CONNECTABLE;

	if (hci_dev_test_flag(hdev, HCI_DISCOVERABLE))
		settings |= MGMT_SETTING_DISCOVERABLE;

	if (hci_dev_test_flag(hdev, HCI_BONDABLE))
		settings |= MGMT_SETTING_BONDABLE;

	if (hci_dev_test_flag(hdev, HCI_BREDR_ENABLED))
		settings |= MGMT_SETTING_BREDR;

	if (hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		settings |= MGMT_SETTING_LE;

	if (hci_dev_test_flag(hdev, HCI_LINK_SECURITY))
		settings |= MGMT_SETTING_LINK_SECURITY;

	if (hci_dev_test_flag(hdev, HCI_SSP_ENABLED))
		settings |= MGMT_SETTING_SSP;

	if (hci_dev_test_flag(hdev, HCI_HS_ENABLED))
		settings |= MGMT_SETTING_HS;

	if (hci_dev_test_flag(hdev, HCI_ADVERTISING))
		settings |= MGMT_SETTING_ADVERTISING;

	if (hci_dev_test_flag(hdev, HCI_SC_ENABLED))
		settings |= MGMT_SETTING_SECURE_CONN;

	if (hci_dev_test_flag(hdev, HCI_KEEP_DEBUG_KEYS))
		settings |= MGMT_SETTING_DEBUG_KEYS;

	if (hci_dev_test_flag(hdev, HCI_PRIVACY))
		settings |= MGMT_SETTING_PRIVACY;

	/* The current setting for static address has two purposes. The
	 * first is to indicate if the static address will be used and
	 * the second is to indicate if it is actually set.
	 *
	 * This means if the static address is not configured, this flag
	 * will never be set. If the address is configured, then if the
	 * address is actually used decides if the flag is set or not.
	 *
	 * For single mode LE only controllers and dual-mode controllers
	 * with BR/EDR disabled, the existence of the static address will
	 * be evaluated.
	 */
	if (hci_dev_test_flag(hdev, HCI_FORCE_STATIC_ADDR) ||
	    !hci_dev_test_flag(hdev, HCI_BREDR_ENABLED) ||
	    !bacmp(&hdev->bdaddr, BDADDR_ANY)) {
		if (bacmp(&hdev->static_addr, BDADDR_ANY))
			settings |= MGMT_SETTING_STATIC_ADDRESS;
	}

	return settings;
}