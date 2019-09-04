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
struct nfc_mei_phy {int /*<<< orphan*/  hdev; } ;
struct mei_cl_device_id {int dummy; } ;
struct mei_cl_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LLC_NOP_NAME ; 
 int /*<<< orphan*/  MEI_NFC_HEADER_SIZE ; 
 int /*<<< orphan*/  MEI_NFC_MAX_HCI_PAYLOAD ; 
 int /*<<< orphan*/  mei_phy_ops ; 
 struct nfc_mei_phy* nfc_mei_phy_alloc (struct mei_cl_device*) ; 
 int /*<<< orphan*/  nfc_mei_phy_free (struct nfc_mei_phy*) ; 
 int pn544_hci_probe (struct nfc_mei_phy*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int pn544_mei_probe(struct mei_cl_device *cldev,
			       const struct mei_cl_device_id *id)
{
	struct nfc_mei_phy *phy;
	int r;

	pr_info("Probing NFC pn544\n");

	phy = nfc_mei_phy_alloc(cldev);
	if (!phy) {
		pr_err("Cannot allocate memory for pn544 mei phy.\n");
		return -ENOMEM;
	}

	r = pn544_hci_probe(phy, &mei_phy_ops, LLC_NOP_NAME,
			    MEI_NFC_HEADER_SIZE, 0, MEI_NFC_MAX_HCI_PAYLOAD,
			    NULL, &phy->hdev);
	if (r < 0) {
		nfc_mei_phy_free(phy);

		return r;
	}

	return 0;
}