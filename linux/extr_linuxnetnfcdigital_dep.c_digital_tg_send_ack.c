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
struct sk_buff {scalar_t__ data; } ;
struct nfc_digital_dev {int curr_nfc_dep_pni; struct sk_buff* saved_skb; int /*<<< orphan*/  (* skb_add_crc ) (struct sk_buff*) ;int /*<<< orphan*/  did; } ;
struct digital_dep_req_res {int pfb; int /*<<< orphan*/  cmd; int /*<<< orphan*/  dir; } ;
struct digital_data_exch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_CMD_DEP_RES ; 
 int /*<<< orphan*/  DIGITAL_NFC_DEP_FRAME_DIR_IN ; 
 int DIGITAL_NFC_DEP_PFB_ACK_NACK_PDU ; 
 int DIGITAL_NFC_DEP_PFB_DID_BIT ; 
 int DIGITAL_NFC_DEP_PFB_PNI (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* digital_skb_alloc (struct nfc_digital_dev*,int) ; 
 int /*<<< orphan*/  digital_skb_push_dep_sod (struct nfc_digital_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  digital_tg_recv_dep_req ; 
 int digital_tg_send_cmd (struct nfc_digital_dev*,struct sk_buff*,int,int /*<<< orphan*/ ,struct digital_data_exch*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* pskb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 

__attribute__((used)) static int digital_tg_send_ack(struct nfc_digital_dev *ddev,
			       struct digital_data_exch *data_exch)
{
	struct digital_dep_req_res *dep_res;
	struct sk_buff *skb;
	int rc;

	skb = digital_skb_alloc(ddev, 1);
	if (!skb)
		return -ENOMEM;

	skb_push(skb, sizeof(struct digital_dep_req_res));

	dep_res = (struct digital_dep_req_res *)skb->data;

	dep_res->dir = DIGITAL_NFC_DEP_FRAME_DIR_IN;
	dep_res->cmd = DIGITAL_CMD_DEP_RES;
	dep_res->pfb = DIGITAL_NFC_DEP_PFB_ACK_NACK_PDU |
		       ddev->curr_nfc_dep_pni;

	if (ddev->did) {
		dep_res->pfb |= DIGITAL_NFC_DEP_PFB_DID_BIT;

		skb_put_data(skb, &ddev->did, sizeof(ddev->did));
	}

	ddev->curr_nfc_dep_pni =
		DIGITAL_NFC_DEP_PFB_PNI(ddev->curr_nfc_dep_pni + 1);

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	ddev->saved_skb = pskb_copy(skb, GFP_KERNEL);

	rc = digital_tg_send_cmd(ddev, skb, 1500, digital_tg_recv_dep_req,
				 data_exch);
	if (rc) {
		kfree_skb(skb);
		kfree_skb(ddev->saved_skb);
		ddev->saved_skb = NULL;
	}

	return rc;
}