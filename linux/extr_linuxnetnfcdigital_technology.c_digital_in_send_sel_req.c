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
struct sk_buff {scalar_t__ data; } ;
struct nfc_target {int nfcid1_len; } ;
struct nfc_digital_dev {int dummy; } ;
struct digital_sel_req {int b2; int /*<<< orphan*/  bcc; int /*<<< orphan*/  nfcid1; int /*<<< orphan*/  sel_cmd; } ;
struct digital_sdd_res {int /*<<< orphan*/  bcc; int /*<<< orphan*/  nfcid1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_CMD_SEL_REQ_CL1 ; 
 int /*<<< orphan*/  DIGITAL_CMD_SEL_REQ_CL2 ; 
 int /*<<< orphan*/  DIGITAL_CMD_SEL_REQ_CL3 ; 
 scalar_t__ DIGITAL_DRV_CAPS_IN_CRC (struct nfc_digital_dev*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_FRAMING ; 
 int /*<<< orphan*/  NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A ; 
 int digital_in_configure_hw (struct nfc_digital_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digital_in_recv_sel_res ; 
 int digital_in_send_cmd (struct nfc_digital_dev*,struct sk_buff*,int,int /*<<< orphan*/ ,struct nfc_target*) ; 
 int /*<<< orphan*/  digital_skb_add_crc_a (struct sk_buff*) ; 
 struct sk_buff* digital_skb_alloc (struct nfc_digital_dev*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int digital_in_send_sel_req(struct nfc_digital_dev *ddev,
				   struct nfc_target *target,
				   struct digital_sdd_res *sdd_res)
{
	struct sk_buff *skb;
	struct digital_sel_req *sel_req;
	u8 sel_cmd;
	int rc;

	skb = digital_skb_alloc(ddev, sizeof(struct digital_sel_req));
	if (!skb)
		return -ENOMEM;

	skb_put(skb, sizeof(struct digital_sel_req));
	sel_req = (struct digital_sel_req *)skb->data;

	if (target->nfcid1_len <= 4)
		sel_cmd = DIGITAL_CMD_SEL_REQ_CL1;
	else if (target->nfcid1_len < 10)
		sel_cmd = DIGITAL_CMD_SEL_REQ_CL2;
	else
		sel_cmd = DIGITAL_CMD_SEL_REQ_CL3;

	sel_req->sel_cmd = sel_cmd;
	sel_req->b2 = 0x70;
	memcpy(sel_req->nfcid1, sdd_res->nfcid1, 4);
	sel_req->bcc = sdd_res->bcc;

	if (DIGITAL_DRV_CAPS_IN_CRC(ddev)) {
		rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A);
		if (rc)
			goto exit;
	} else {
		digital_skb_add_crc_a(skb);
	}

	rc = digital_in_send_cmd(ddev, skb, 30, digital_in_recv_sel_res,
				 target);
exit:
	if (rc)
		kfree_skb(skb);

	return rc;
}