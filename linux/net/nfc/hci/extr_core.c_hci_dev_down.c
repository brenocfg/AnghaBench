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
struct nfc_hci_dev {TYPE_1__* ops; int /*<<< orphan*/  llc; } ;
struct nfc_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (struct nfc_hci_dev*) ;} ;

/* Variables and functions */
 struct nfc_hci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int /*<<< orphan*/  nfc_hci_reset_pipes (struct nfc_hci_dev*) ; 
 int /*<<< orphan*/  nfc_llc_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nfc_hci_dev*) ; 

__attribute__((used)) static int hci_dev_down(struct nfc_dev *nfc_dev)
{
	struct nfc_hci_dev *hdev = nfc_get_drvdata(nfc_dev);

	nfc_llc_stop(hdev->llc);

	if (hdev->ops->close)
		hdev->ops->close(hdev);

	nfc_hci_reset_pipes(hdev);

	return 0;
}