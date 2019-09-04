#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfc_hci_dev {TYPE_1__* ops; } ;
struct nfc_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop_poll ) (struct nfc_hci_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_HCI_EVT_END_OPERATION ; 
 int /*<<< orphan*/  NFC_HCI_RF_READER_A_GATE ; 
 struct nfc_hci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  nfc_hci_send_event (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nfc_hci_dev*) ; 

__attribute__((used)) static void hci_stop_poll(struct nfc_dev *nfc_dev)
{
	struct nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	if (hdev->ops->stop_poll)
		hdev->ops->stop_poll(hdev);
	else
		nfc_hci_send_event(hdev, NFC_HCI_RF_READER_A_GATE,
				   NFC_HCI_EVT_END_OPERATION, NULL, 0);
}