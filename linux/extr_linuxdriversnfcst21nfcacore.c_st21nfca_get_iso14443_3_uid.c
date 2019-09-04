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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct nfc_hci_dev {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int NFC_NFCID1_MAXSIZE ; 
 int /*<<< orphan*/  ST21NFCA_RF_READER_14443_3_A_GATE ; 
 int /*<<< orphan*/  ST21NFCA_RF_READER_14443_3_A_UID ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nfc_hci_get_param (struct nfc_hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff**) ; 

__attribute__((used)) static int st21nfca_get_iso14443_3_uid(struct nfc_hci_dev *hdev, u8 *uid,
				       int *len)
{
	int r;
	struct sk_buff *uid_skb = NULL;

	r = nfc_hci_get_param(hdev, ST21NFCA_RF_READER_14443_3_A_GATE,
			      ST21NFCA_RF_READER_14443_3_A_UID, &uid_skb);
	if (r < 0)
		goto exit;

	if (uid_skb->len == 0 || uid_skb->len > NFC_NFCID1_MAXSIZE) {
		r = -EPROTO;
		goto exit;
	}

	memcpy(uid, uid_skb->data, uid_skb->len);
	*len = uid_skb->len;
exit:
	kfree_skb(uid_skb);
	return r;
}