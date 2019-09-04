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
struct TYPE_2__ {int /*<<< orphan*/  curr_nfc_dep_pni; } ;
struct st21nfca_hci_info {TYPE_1__ dep_info; } ;
struct st21nfca_dep_req_res {int /*<<< orphan*/  pfb; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct nfc_hci_dev {int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ ST21NFCA_NFC_DEP_DID_BIT_SET (int /*<<< orphan*/ ) ; 
 scalar_t__ ST21NFCA_NFC_DEP_NAD_BIT_SET (int /*<<< orphan*/ ) ; 
#define  ST21NFCA_NFC_DEP_PFB_ACK_NACK_PDU 130 
#define  ST21NFCA_NFC_DEP_PFB_I_PDU 129 
 int /*<<< orphan*/  ST21NFCA_NFC_DEP_PFB_PNI (int /*<<< orphan*/ ) ; 
#define  ST21NFCA_NFC_DEP_PFB_SUPERVISOR_PDU 128 
 int ST21NFCA_NFC_DEP_PFB_TYPE (int /*<<< orphan*/ ) ; 
 struct st21nfca_hci_info* nfc_hci_get_clientdata (struct nfc_hci_dev*) ; 
 int nfc_tm_data_received (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static int st21nfca_tm_recv_dep_req(struct nfc_hci_dev *hdev,
				    struct sk_buff *skb)
{
	struct st21nfca_dep_req_res *dep_req;
	u8 size;
	int r;
	struct st21nfca_hci_info *info = nfc_hci_get_clientdata(hdev);

	skb_trim(skb, skb->len - 1);

	size = 4;

	dep_req = (struct st21nfca_dep_req_res *)skb->data;
	if (skb->len < size) {
		r = -EIO;
		goto exit;
	}

	if (ST21NFCA_NFC_DEP_DID_BIT_SET(dep_req->pfb))
		size++;
	if (ST21NFCA_NFC_DEP_NAD_BIT_SET(dep_req->pfb))
		size++;

	if (skb->len < size) {
		r = -EIO;
		goto exit;
	}

	/* Receiving DEP_REQ - Decoding */
	switch (ST21NFCA_NFC_DEP_PFB_TYPE(dep_req->pfb)) {
	case ST21NFCA_NFC_DEP_PFB_I_PDU:
		info->dep_info.curr_nfc_dep_pni =
				ST21NFCA_NFC_DEP_PFB_PNI(dep_req->pfb);
		break;
	case ST21NFCA_NFC_DEP_PFB_ACK_NACK_PDU:
		pr_err("Received a ACK/NACK PDU\n");
		break;
	case ST21NFCA_NFC_DEP_PFB_SUPERVISOR_PDU:
		pr_err("Received a SUPERVISOR PDU\n");
		break;
	}

	skb_pull(skb, size);

	return nfc_tm_data_received(hdev->ndev, skb);
exit:
	return r;
}