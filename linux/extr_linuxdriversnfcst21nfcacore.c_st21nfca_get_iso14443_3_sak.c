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
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  ST21NFCA_RF_READER_14443_3_A_GATE ; 
 int /*<<< orphan*/  ST21NFCA_RF_READER_14443_3_A_SAK ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int nfc_hci_get_param (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff**) ; 

__attribute__((used)) static int st21nfca_get_iso14443_3_sak(struct nfc_hci_dev *hdev, u8 *sak)
{
	int r;
	struct sk_buff *sak_skb = NULL;

	r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_14443_3_A_GATE,
			      ST21NFCA_RF_READER_14443_3_A_SAK, &sak_skb);
	if (r < 0)
		goto exit;

	if (sak_skb->len != 1) {
		r = -EPROTO;
		goto exit;
	}

	*sak = sak_skb->data[0];

exit:
	kfree_skb(sak_skb);
	return r;
}