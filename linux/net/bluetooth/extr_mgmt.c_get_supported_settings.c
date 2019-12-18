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
struct hci_dev {scalar_t__ hci_ver; scalar_t__ set_bdaddr; int /*<<< orphan*/  quirks; } ;

/* Variables and functions */
 scalar_t__ BLUETOOTH_VER_1_2 ; 
 int /*<<< orphan*/  HCI_QUIRK_EXTERNAL_CONFIG ; 
 int /*<<< orphan*/  MGMT_SETTING_ADVERTISING ; 
 int /*<<< orphan*/  MGMT_SETTING_BONDABLE ; 
 int /*<<< orphan*/  MGMT_SETTING_BREDR ; 
 int /*<<< orphan*/  MGMT_SETTING_CONFIGURATION ; 
 int /*<<< orphan*/  MGMT_SETTING_CONNECTABLE ; 
 int /*<<< orphan*/  MGMT_SETTING_DEBUG_KEYS ; 
 int /*<<< orphan*/  MGMT_SETTING_DISCOVERABLE ; 
 int /*<<< orphan*/  MGMT_SETTING_FAST_CONNECTABLE ; 
 int /*<<< orphan*/  MGMT_SETTING_HS ; 
 int /*<<< orphan*/  MGMT_SETTING_LE ; 
 int /*<<< orphan*/  MGMT_SETTING_LINK_SECURITY ; 
 int /*<<< orphan*/  MGMT_SETTING_PHY_CONFIGURATION ; 
 int /*<<< orphan*/  MGMT_SETTING_POWERED ; 
 int /*<<< orphan*/  MGMT_SETTING_PRIVACY ; 
 int /*<<< orphan*/  MGMT_SETTING_SECURE_CONN ; 
 int /*<<< orphan*/  MGMT_SETTING_SSP ; 
 int /*<<< orphan*/  MGMT_SETTING_STATIC_ADDRESS ; 
 scalar_t__ lmp_bredr_capable (struct hci_dev*) ; 
 scalar_t__ lmp_le_capable (struct hci_dev*) ; 
 scalar_t__ lmp_sc_capable (struct hci_dev*) ; 
 scalar_t__ lmp_ssp_capable (struct hci_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 get_supported_settings(struct hci_dev *hdev)
{
	u32 settings = 0;

	settings |= MGMT_SETTING_POWERED;
	settings |= MGMT_SETTING_BONDABLE;
	settings |= MGMT_SETTING_DEBUG_KEYS;
	settings |= MGMT_SETTING_CONNECTABLE;
	settings |= MGMT_SETTING_DISCOVERABLE;

	if (lmp_bredr_capable(hdev)) {
		if (hdev->hci_ver >= BLUETOOTH_VER_1_2)
			settings |= MGMT_SETTING_FAST_CONNECTABLE;
		settings |= MGMT_SETTING_BREDR;
		settings |= MGMT_SETTING_LINK_SECURITY;

		if (lmp_ssp_capable(hdev)) {
			settings |= MGMT_SETTING_SSP;
			settings |= MGMT_SETTING_HS;
		}

		if (lmp_sc_capable(hdev))
			settings |= MGMT_SETTING_SECURE_CONN;
	}

	if (lmp_le_capable(hdev)) {
		settings |= MGMT_SETTING_LE;
		settings |= MGMT_SETTING_ADVERTISING;
		settings |= MGMT_SETTING_SECURE_CONN;
		settings |= MGMT_SETTING_PRIVACY;
		settings |= MGMT_SETTING_STATIC_ADDRESS;
	}

	if (test_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks) ||
	    hdev->set_bdaddr)
		settings |= MGMT_SETTING_CONFIGURATION;

	settings |= MGMT_SETTING_PHY_CONFIGURATION;

	return settings;
}