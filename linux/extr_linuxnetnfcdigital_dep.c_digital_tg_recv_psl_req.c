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
typedef  int u8 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct nfc_digital_dev {int (* skb_check_crc ) (struct sk_buff*) ;int local_payload_max; int remote_payload_max; } ;
struct digital_psl_req {scalar_t__ dir; scalar_t__ cmd; int brs; int /*<<< orphan*/  did; int /*<<< orphan*/  fsl; } ;

/* Variables and functions */
 scalar_t__ DIGITAL_CMD_PSL_REQ ; 
 scalar_t__ DIGITAL_NFC_DEP_FRAME_DIR_OUT ; 
 int DIGITAL_PAYLOAD_FSL_TO_BITS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int NFC_DIGITAL_RF_TECH_106A ; 
 int NFC_DIGITAL_RF_TECH_212F ; 
 int NFC_DIGITAL_RF_TECH_424F ; 
 int /*<<< orphan*/  PROTOCOL_ERR (char*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int digital_payload_bits_to_size (int) ; 
 int digital_skb_pull_dep_sod (struct nfc_digital_dev*,struct sk_buff*) ; 
 int digital_tg_send_psl_res (struct nfc_digital_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int stub1 (struct sk_buff*) ; 

__attribute__((used)) static void digital_tg_recv_psl_req(struct nfc_digital_dev *ddev, void *arg,
				    struct sk_buff *resp)
{
	int rc;
	struct digital_psl_req *psl_req;
	u8 rf_tech;
	u8 dsi, payload_size, payload_bits;

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);
		resp = NULL;
		goto exit;
	}

	rc = ddev->skb_check_crc(resp);
	if (rc) {
		PROTOCOL_ERR("14.4.1.6");
		goto exit;
	}

	rc = digital_skb_pull_dep_sod(ddev, resp);
	if (rc) {
		PROTOCOL_ERR("14.4.1.2");
		goto exit;
	}

	psl_req = (struct digital_psl_req *)resp->data;

	if (resp->len != sizeof(struct digital_psl_req) ||
	    psl_req->dir != DIGITAL_NFC_DEP_FRAME_DIR_OUT ||
	    psl_req->cmd != DIGITAL_CMD_PSL_REQ) {
		rc = -EIO;
		goto exit;
	}

	dsi = (psl_req->brs >> 3) & 0x07;
	switch (dsi) {
	case 0:
		rf_tech = NFC_DIGITAL_RF_TECH_106A;
		break;
	case 1:
		rf_tech = NFC_DIGITAL_RF_TECH_212F;
		break;
	case 2:
		rf_tech = NFC_DIGITAL_RF_TECH_424F;
		break;
	default:
		pr_err("Unsupported dsi value %d\n", dsi);
		goto exit;
	}

	payload_bits = DIGITAL_PAYLOAD_FSL_TO_BITS(psl_req->fsl);
	payload_size = digital_payload_bits_to_size(payload_bits);

	if (!payload_size || (payload_size > min(ddev->local_payload_max,
						 ddev->remote_payload_max))) {
		rc = -EINVAL;
		goto exit;
	}

	ddev->local_payload_max = payload_size;
	ddev->remote_payload_max = payload_size;

	rc = digital_tg_send_psl_res(ddev, psl_req->did, rf_tech);

exit:
	kfree_skb(resp);
}