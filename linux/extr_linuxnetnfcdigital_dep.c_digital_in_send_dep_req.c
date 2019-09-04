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
struct nfc_target {int dummy; } ;
struct nfc_digital_dev {struct sk_buff* saved_skb; struct sk_buff* chaining_skb; int /*<<< orphan*/  dep_rwt; int /*<<< orphan*/  (* skb_add_crc ) (struct sk_buff*) ;scalar_t__ nack_count; scalar_t__ atn_count; int /*<<< orphan*/  curr_nfc_dep_pni; } ;
struct digital_dep_req_res {int /*<<< orphan*/  pfb; int /*<<< orphan*/  cmd; int /*<<< orphan*/  dir; } ;
struct digital_data_exch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_CMD_DEP_REQ ; 
 int /*<<< orphan*/  DIGITAL_NFC_DEP_FRAME_DIR_OUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  digital_in_recv_dep_res ; 
 int digital_in_send_cmd (struct nfc_digital_dev*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct digital_data_exch*) ; 
 struct sk_buff* digital_send_dep_data_prep (struct nfc_digital_dev*,struct sk_buff*,struct digital_dep_req_res*,struct digital_data_exch*) ; 
 int /*<<< orphan*/  digital_skb_push_dep_sod (struct nfc_digital_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* pskb_copy (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 

int digital_in_send_dep_req(struct nfc_digital_dev *ddev,
			    struct nfc_target *target, struct sk_buff *skb,
			    struct digital_data_exch *data_exch)
{
	struct digital_dep_req_res *dep_req;
	struct sk_buff *chaining_skb, *tmp_skb;
	int rc;

	skb_push(skb, sizeof(struct digital_dep_req_res));

	dep_req = (struct digital_dep_req_res *)skb->data;

	dep_req->dir = DIGITAL_NFC_DEP_FRAME_DIR_OUT;
	dep_req->cmd = DIGITAL_CMD_DEP_REQ;
	dep_req->pfb = ddev->curr_nfc_dep_pni;

	ddev->atn_count = 0;
	ddev->nack_count = 0;

	chaining_skb = ddev->chaining_skb;

	tmp_skb = digital_send_dep_data_prep(ddev, skb, dep_req, data_exch);
	if (IS_ERR(tmp_skb))
		return PTR_ERR(tmp_skb);

	digital_skb_push_dep_sod(ddev, tmp_skb);

	ddev->skb_add_crc(tmp_skb);

	ddev->saved_skb = pskb_copy(tmp_skb, GFP_KERNEL);

	rc = digital_in_send_cmd(ddev, tmp_skb, ddev->dep_rwt,
				 digital_in_recv_dep_res, data_exch);
	if (rc) {
		if (tmp_skb != skb)
			kfree_skb(tmp_skb);

		kfree_skb(chaining_skb);
		ddev->chaining_skb = NULL;

		kfree_skb(ddev->saved_skb);
		ddev->saved_skb = NULL;
	}

	return rc;
}