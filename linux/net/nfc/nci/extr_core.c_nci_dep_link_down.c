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
struct nfc_dev {scalar_t__ rf_mode; } ;
struct nci_dev {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_DEACTIVATE_TYPE_IDLE_MODE ; 
 scalar_t__ NCI_DISCOVERY ; 
 scalar_t__ NCI_LISTEN_ACTIVE ; 
 int /*<<< orphan*/  NCI_RF_DEACTIVATE_TIMEOUT ; 
 scalar_t__ NFC_RF_INITIATOR ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_deactivate_target (struct nfc_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_request (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nci_rf_deactivate_req ; 
 struct nci_dev* nfc_get_drvdata (struct nfc_dev*) ; 
 int nfc_tm_deactivated (struct nfc_dev*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int nci_dep_link_down(struct nfc_dev *nfc_dev)
{
	struct nci_dev *ndev = nfc_get_drvdata(nfc_dev);
	int rc;

	pr_debug("entry\n");

	if (nfc_dev->rf_mode == NFC_RF_INITIATOR) {
		nci_deactivate_target(nfc_dev, NULL, NCI_DEACTIVATE_TYPE_IDLE_MODE);
	} else {
		if (atomic_read(&ndev->state) == NCI_LISTEN_ACTIVE ||
		    atomic_read(&ndev->state) == NCI_DISCOVERY) {
			nci_request(ndev, nci_rf_deactivate_req, 0,
				msecs_to_jiffies(NCI_RF_DEACTIVATE_TIMEOUT));
		}

		rc = nfc_tm_deactivated(nfc_dev);
		if (rc)
			pr_err("error when signaling tm deactivation\n");
	}

	return 0;
}