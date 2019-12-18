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
typedef  int /*<<< orphan*/  u8 ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_LE_ENABLED ; 
 int /*<<< orphan*/  MGMT_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  MGMT_STATUS_REJECTED ; 
 int /*<<< orphan*/  MGMT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmp_le_capable (struct hci_dev*) ; 

__attribute__((used)) static u8 mgmt_le_support(struct hci_dev *hdev)
{
	if (!lmp_le_capable(hdev))
		return MGMT_STATUS_NOT_SUPPORTED;
	else if (!hci_dev_test_flag(hdev, HCI_LE_ENABLED))
		return MGMT_STATUS_REJECTED;
	else
		return MGMT_STATUS_SUCCESS;
}