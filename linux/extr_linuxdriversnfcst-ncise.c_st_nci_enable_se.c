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
typedef  int /*<<< orphan*/  u32 ;
struct nci_dev {int /*<<< orphan*/  nfc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_NCI_APDU_READER_GATE ; 
 int ST_NCI_ESE_HOST_ID ; 
 int /*<<< orphan*/  ST_NCI_EVT_SE_SOFT_RESET ; 
 int /*<<< orphan*/  ST_NCI_SE_MODE_ON ; 
 int nci_hci_send_event (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_remove_se (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int st_nci_control_se (struct nci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_nci_se_get_atr (struct nci_dev*) ; 

int st_nci_enable_se(struct nci_dev *ndev, u32 se_idx)
{
	int r;

	pr_debug("st_nci_enable_se\n");

	/*
	 * According to upper layer, se_idx == NFC_SE_UICC when
	 * info->se_info.se_status->is_uicc_enable is true should never happen.
	 * Same for eSE.
	 */
	r = st_nci_control_se(ndev, se_idx, ST_NCI_SE_MODE_ON);
	if (r == ST_NCI_ESE_HOST_ID) {
		st_nci_se_get_atr(ndev);
		r = nci_hci_send_event(ndev, ST_NCI_APDU_READER_GATE,
				ST_NCI_EVT_SE_SOFT_RESET, NULL, 0);
	}

	if (r < 0) {
		/*
		 * The activation procedure failed, the secure element
		 * is not connected. Remove from the list.
		 */
		nfc_remove_se(ndev->nfc_dev, se_idx);
		return r;
	}

	return 0;
}