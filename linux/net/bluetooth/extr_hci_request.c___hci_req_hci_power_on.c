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
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_CMD_TIMEOUT ; 
 int __hci_req_sync (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  powered_update_hci ; 
 int /*<<< orphan*/  smp_register (struct hci_dev*) ; 

int __hci_req_hci_power_on(struct hci_dev *hdev)
{
	/* Register the available SMP channels (BR/EDR and LE) only when
	 * successfully powering on the controller. This late
	 * registration is required so that LE SMP can clearly decide if
	 * the public address or static address is used.
	 */
	smp_register(hdev);

	return __hci_req_sync(hdev, powered_update_hci, 0, HCI_CMD_TIMEOUT,
			      NULL);
}