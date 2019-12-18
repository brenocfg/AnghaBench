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
struct hci_dev {int /*<<< orphan*/  public_addr; int /*<<< orphan*/  quirks; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_ANY ; 
 int /*<<< orphan*/  HCI_EXT_CONFIGURED ; 
 int /*<<< orphan*/  HCI_QUIRK_EXTERNAL_CONFIG ; 
 int /*<<< orphan*/  HCI_QUIRK_INVALID_BDADDR ; 
 int /*<<< orphan*/  HCI_QUIRK_USE_BDADDR_PROPERTY ; 
 int /*<<< orphan*/  MGMT_OPTION_EXTERNAL_CONFIG ; 
 int /*<<< orphan*/  MGMT_OPTION_PUBLIC_ADDRESS ; 
 int /*<<< orphan*/  bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __le32 get_missing_options(struct hci_dev *hdev)
{
	u32 options = 0;

	if (test_bit(HCI_QUIRK_EXTERNAL_CONFIG, &hdev->quirks) &&
	    !hci_dev_test_flag(hdev, HCI_EXT_CONFIGURED))
		options |= MGMT_OPTION_EXTERNAL_CONFIG;

	if ((test_bit(HCI_QUIRK_INVALID_BDADDR, &hdev->quirks) ||
	     test_bit(HCI_QUIRK_USE_BDADDR_PROPERTY, &hdev->quirks)) &&
	    !bacmp(&hdev->public_addr, BDADDR_ANY))
		options |= MGMT_OPTION_PUBLIC_ADDRESS;

	return cpu_to_le32(options);
}