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
struct nci_dev {int /*<<< orphan*/  hci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_HCI_ADMIN_GATE ; 
 int /*<<< orphan*/  NCI_HCI_ADM_CLEAR_ALL_PIPE ; 
 int /*<<< orphan*/  nci_hci_reset_pipes (int /*<<< orphan*/ ) ; 
 int nci_hci_send_cmd (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nci_hci_clear_all_pipes(struct nci_dev *ndev)
{
	int r;

	r = nci_hci_send_cmd(ndev, NCI_HCI_ADMIN_GATE,
			     NCI_HCI_ADM_CLEAR_ALL_PIPE, NULL, 0, NULL);
	if (r < 0)
		return r;

	nci_hci_reset_pipes(ndev->hci_dev);
	return r;
}