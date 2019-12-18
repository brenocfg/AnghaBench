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
struct sk_buff {int len; scalar_t__ data; } ;
struct nfc_target {int /*<<< orphan*/  idx; } ;
struct nfc_digital_dev {int (* skb_check_crc ) (struct sk_buff*) ;scalar_t__ curr_rf_tech; scalar_t__ curr_protocol; scalar_t__ curr_nfc_dep_pni; int /*<<< orphan*/  nfc_dev; int /*<<< orphan*/  skb_add_crc; } ;
struct digital_psl_res {scalar_t__ dir; scalar_t__ cmd; } ;

/* Variables and functions */
 scalar_t__ DIGITAL_CMD_PSL_RES ; 
 int /*<<< orphan*/  DIGITAL_DRV_CAPS_IN_CRC (struct nfc_digital_dev*) ; 
 scalar_t__ DIGITAL_NFC_DEP_FRAME_DIR_IN ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  NFC_COMM_ACTIVE ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_FRAMING ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_RF_TECH ; 
 scalar_t__ NFC_DIGITAL_FRAMING_NFCF_NFC_DEP ; 
 scalar_t__ NFC_DIGITAL_RF_TECH_106A ; 
 scalar_t__ NFC_DIGITAL_RF_TECH_424F ; 
 int /*<<< orphan*/  NFC_RF_INITIATOR ; 
 int /*<<< orphan*/  PROTOCOL_ERR (char*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int digital_in_configure_hw (struct nfc_digital_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  digital_skb_add_crc_f ; 
 int digital_skb_check_crc_f (struct sk_buff*) ; 
 int digital_skb_pull_dep_sod (struct nfc_digital_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  nfc_dep_link_is_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct sk_buff*) ; 

__attribute__((used)) static void digital_in_recv_psl_res(struct nfc_digital_dev *ddev, void *arg,
				    struct sk_buff *resp)
{
	struct nfc_target *target = arg;
	struct digital_psl_res *psl_res;
	int rc;

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

	psl_res = (struct digital_psl_res *)resp->data;

	if ((resp->len != sizeof(*psl_res)) ||
	    (psl_res->dir != DIGITAL_NFC_DEP_FRAME_DIR_IN) ||
	    (psl_res->cmd != DIGITAL_CMD_PSL_RES)) {
		rc = -EIO;
		goto exit;
	}

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH,
				     NFC_DIGITAL_RF_TECH_424F);
	if (rc)
		goto exit;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFCF_NFC_DEP);
	if (rc)
		goto exit;

	if (!DIGITAL_DRV_CAPS_IN_CRC(ddev) &&
	    (ddev->curr_rf_tech == NFC_DIGITAL_RF_TECH_106A)) {
		ddev->skb_add_crc = digital_skb_add_crc_f;
		ddev->skb_check_crc = digital_skb_check_crc_f;
	}

	ddev->curr_rf_tech = NFC_DIGITAL_RF_TECH_424F;

	nfc_dep_link_is_up(ddev->nfc_dev, target->idx, NFC_COMM_ACTIVE,
			   NFC_RF_INITIATOR);

	ddev->curr_nfc_dep_pni = 0;

exit:
	dev_kfree_skb(resp);

	if (rc)
		ddev->curr_protocol = 0;
}