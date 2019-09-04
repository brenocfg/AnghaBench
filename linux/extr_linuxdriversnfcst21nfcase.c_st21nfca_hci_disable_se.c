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
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST21NFCA_SE_MODE_OFF ; 
 int st21nfca_hci_control_se (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int st21nfca_hci_disable_se(struct nfc_hci_dev *hdev, u32 se_idx)
{
	int r;

	/*
	 * According to upper layer, se_idx == NFC_SE_UICC when
	 * info->se_status->is_uicc_enable is true should never happen
	 * Same for eSE.
	 */
	r = st21nfca_hci_control_se(hdev, se_idx, ST21NFCA_SE_MODE_OFF);
	if (r < 0)
		return r;

	return 0;
}