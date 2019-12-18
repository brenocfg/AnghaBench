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
struct nfc_hci_dev {int /*<<< orphan*/  msg_tx_mutex; int /*<<< orphan*/  ndev; int /*<<< orphan*/ * cmd_pending_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nfc_hci_cmd_completion (struct nfc_hci_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfc_driver_failure (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nfc_hci_failure(struct nfc_hci_dev *hdev, int err)
{
	mutex_lock(&hdev->msg_tx_mutex);

	if (hdev->cmd_pending_msg == NULL) {
		nfc_driver_failure(hdev->ndev, err);
		goto exit;
	}

	__nfc_hci_cmd_completion(hdev, err, NULL);

exit:
	mutex_unlock(&hdev->msg_tx_mutex);
}