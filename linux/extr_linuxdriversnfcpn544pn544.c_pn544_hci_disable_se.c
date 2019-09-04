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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nfc_se {int type; } ;
struct nfc_hci_dev {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NFC_SE_EMBEDDED 129 
#define  NFC_SE_UICC 128 
 int /*<<< orphan*/  PN544_NFC_ESE_DEFAULT_MODE ; 
 int /*<<< orphan*/  PN544_NFC_WI_MGMT_GATE ; 
 int /*<<< orphan*/  PN544_SE_MODE_OFF ; 
 int /*<<< orphan*/  PN544_SWP_DEFAULT_MODE ; 
 int /*<<< orphan*/  PN544_SWP_MGMT_GATE ; 
 struct nfc_se* nfc_find_se (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfc_hci_set_param (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int pn544_hci_disable_se(struct nfc_hci_dev *hdev, u32 se_idx)
{
	struct nfc_se *se;
	u8 disable = PN544_SE_MODE_OFF;

	se = nfc_find_se(hdev->ndev, se_idx);

	switch (se->type) {
	case NFC_SE_UICC:
		return nfc_hci_set_param(hdev, PN544_SWP_MGMT_GATE,
			      PN544_SWP_DEFAULT_MODE, &disable, 1);
	case NFC_SE_EMBEDDED:
		return nfc_hci_set_param(hdev, PN544_NFC_WI_MGMT_GATE,
			      PN544_NFC_ESE_DEFAULT_MODE, &disable, 1);
	default:
		return -EINVAL;
	}
}