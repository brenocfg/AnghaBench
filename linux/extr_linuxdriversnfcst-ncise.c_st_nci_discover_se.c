#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {TYPE_1__* se_status; } ;
struct st_nci_info {TYPE_2__ se_info; int /*<<< orphan*/  flags; } ;
struct nci_dev {int /*<<< orphan*/  nfc_dev; } ;
struct TYPE_3__ {scalar_t__ is_ese_present; scalar_t__ is_uicc_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCI_HCI_ADMIN_GATE ; 
 int /*<<< orphan*/  NCI_HCI_ADMIN_PARAM_WHITELIST ; 
 int NCI_HCI_ANY_OK ; 
 int /*<<< orphan*/  NFC_SE_EMBEDDED ; 
 int /*<<< orphan*/  NFC_SE_UICC ; 
 int /*<<< orphan*/  ST_NCI_ESE_HOST_ID ; 
 int /*<<< orphan*/  ST_NCI_FACTORY_MODE ; 
 int /*<<< orphan*/  ST_NCI_UICC_HOST_ID ; 
 struct st_nci_info* nci_get_drvdata (struct nci_dev*) ; 
 int nci_hci_set_param (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfc_add_se (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int st_nci_hci_network_init (struct nci_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int st_nci_discover_se(struct nci_dev *ndev)
{
	u8 white_list[2];
	int r, wl_size = 0;
	int se_count = 0;
	struct st_nci_info *info = nci_get_drvdata(ndev);

	pr_debug("st_nci_discover_se\n");

	r = st_nci_hci_network_init(ndev);
	if (r != 0)
		return r;

	if (test_bit(ST_NCI_FACTORY_MODE, &info->flags))
		return 0;

	if (info->se_info.se_status->is_uicc_present)
		white_list[wl_size++] = ST_NCI_UICC_HOST_ID;
	if (info->se_info.se_status->is_ese_present)
		white_list[wl_size++] = ST_NCI_ESE_HOST_ID;

	if (wl_size) {
		r = nci_hci_set_param(ndev, NCI_HCI_ADMIN_GATE,
				      NCI_HCI_ADMIN_PARAM_WHITELIST,
				      white_list, wl_size);
		if (r != NCI_HCI_ANY_OK)
			return r;
	}

	if (info->se_info.se_status->is_uicc_present) {
		nfc_add_se(ndev->nfc_dev, ST_NCI_UICC_HOST_ID, NFC_SE_UICC);
		se_count++;
	}

	if (info->se_info.se_status->is_ese_present) {
		nfc_add_se(ndev->nfc_dev, ST_NCI_ESE_HOST_ID, NFC_SE_EMBEDDED);
		se_count++;
	}

	return !se_count;
}