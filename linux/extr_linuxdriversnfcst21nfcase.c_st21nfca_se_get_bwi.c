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
typedef  int u8 ;
struct TYPE_2__ {int* atr; } ;
struct st21nfca_hci_info {TYPE_1__ se_info; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int ST21NFCA_ATR_DEFAULT_BWI ; 
 int ST21NFCA_ATR_GET_Y_FROM_TD (int) ; 
 scalar_t__ ST21NFCA_ATR_TA_PRESENT (int) ; 
 scalar_t__ ST21NFCA_ATR_TB_PRESENT (int) ; 
 int ST21NFCA_ESE_MAX_LENGTH ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 

__attribute__((used)) static u8 st21nfca_se_get_bwi(struct nfc_hci_dev *hdev)
{
	int i;
	u8 td;
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	/* Bits 8 to 5 of the first TB for T=1 encode BWI from zero to nine */
	for (i = 1; i < ST21NFCA_ESE_MAX_LENGTH; i++) {
		td = ST21NFCA_ATR_GET_Y_FROM_TD(info->se_info.atr[i]);
		if (ST21NFCA_ATR_TA_PRESENT(td))
			i++;
		if (ST21NFCA_ATR_TB_PRESENT(td)) {
			i++;
			return info->se_info.atr[i] >> 4;
		}
	}
	return ST21NFCA_ATR_DEFAULT_BWI;
}