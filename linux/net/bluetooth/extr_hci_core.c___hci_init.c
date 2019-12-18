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
struct hci_dev {scalar_t__ dev_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CONFIG ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 scalar_t__ HCI_PRIMARY ; 
 int /*<<< orphan*/  HCI_SETUP ; 
 int __hci_req_sync (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_debugfs_create_basic (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_debugfs_create_bredr (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_debugfs_create_common (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_debugfs_create_le (struct hci_dev*) ; 
 scalar_t__ hci_dev_test_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_init1_req ; 
 int /*<<< orphan*/  hci_init2_req ; 
 int /*<<< orphan*/  hci_init3_req ; 
 int /*<<< orphan*/  hci_init4_req ; 
 scalar_t__ lmp_bredr_capable (struct hci_dev*) ; 
 scalar_t__ lmp_le_capable (struct hci_dev*) ; 

__attribute__((used)) static int __hci_init(struct hci_dev *hdev)
{
	int err;

	err = __hci_req_sync(hdev, hci_init1_req, 0, HCI_INIT_TIMEOUT, NULL);
	if (err < 0)
		return err;

	if (hci_dev_test_flag(hdev, HCI_SETUP))
		hci_debugfs_create_basic(hdev);

	err = __hci_req_sync(hdev, hci_init2_req, 0, HCI_INIT_TIMEOUT, NULL);
	if (err < 0)
		return err;

	/* HCI_PRIMARY covers both single-mode LE, BR/EDR and dual-mode
	 * BR/EDR/LE type controllers. AMP controllers only need the
	 * first two stages of init.
	 */
	if (hdev->dev_type != HCI_PRIMARY)
		return 0;

	err = __hci_req_sync(hdev, hci_init3_req, 0, HCI_INIT_TIMEOUT, NULL);
	if (err < 0)
		return err;

	err = __hci_req_sync(hdev, hci_init4_req, 0, HCI_INIT_TIMEOUT, NULL);
	if (err < 0)
		return err;

	/* This function is only called when the controller is actually in
	 * configured state. When the controller is marked as unconfigured,
	 * this initialization procedure is not run.
	 *
	 * It means that it is possible that a controller runs through its
	 * setup phase and then discovers missing settings. If that is the
	 * case, then this function will not be called. It then will only
	 * be called during the config phase.
	 *
	 * So only when in setup phase or config phase, create the debugfs
	 * entries and register the SMP channels.
	 */
	if (!hci_dev_test_flag(hdev, HCI_SETUP) &&
	    !hci_dev_test_flag(hdev, HCI_CONFIG))
		return 0;

	hci_debugfs_create_common(hdev);

	if (lmp_bredr_capable(hdev))
		hci_debugfs_create_bredr(hdev);

	if (lmp_le_capable(hdev))
		hci_debugfs_create_le(hdev);

	return 0;
}