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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct nfc_target {int /*<<< orphan*/  sel_res; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_DRV_CAPS_IN_CRC (struct nfc_digital_dev*) ; 
 scalar_t__ DIGITAL_SEL_RES_IS_NFC_DEP (int /*<<< orphan*/ ) ; 
 scalar_t__ DIGITAL_SEL_RES_IS_T2T (int /*<<< orphan*/ ) ; 
 scalar_t__ DIGITAL_SEL_RES_IS_T4T (int /*<<< orphan*/ ) ; 
 scalar_t__ DIGITAL_SEL_RES_LEN ; 
 int /*<<< orphan*/  DIGITAL_SEL_RES_NFCID1_COMPLETE (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  NFC_PROTO_MIFARE ; 
 int /*<<< orphan*/  NFC_PROTO_NFC_DEP ; 
 int /*<<< orphan*/  PROTOCOL_ERR (char*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int digital_in_send_rats (struct nfc_digital_dev*,struct nfc_target*) ; 
 int digital_in_send_sdd_req (struct nfc_digital_dev*,struct nfc_target*) ; 
 int /*<<< orphan*/  digital_poll_next_tech (struct nfc_digital_dev*) ; 
 int digital_skb_check_crc_a (struct sk_buff*) ; 
 int digital_target_found (struct nfc_digital_dev*,struct nfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfc_target*) ; 

__attribute__((used)) static void digital_in_recv_sel_res(struct nfc_digital_dev *ddev, void *arg,
				    struct sk_buff *resp)
{
	struct nfc_target *target = arg;
	int rc;
	u8 sel_res;
	u8 nfc_proto;

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);
		resp = NULL;
		goto exit;
	}

	if (!DIGITAL_DRV_CAPS_IN_CRC(ddev)) {
		rc = digital_skb_check_crc_a(resp);
		if (rc) {
			PROTOCOL_ERR("4.4.1.3");
			goto exit;
		}
	}

	if (resp->len != DIGITAL_SEL_RES_LEN) {
		rc = -EIO;
		goto exit;
	}

	sel_res = resp->data[0];

	if (!DIGITAL_SEL_RES_NFCID1_COMPLETE(sel_res)) {
		rc = digital_in_send_sdd_req(ddev, target);
		if (rc)
			goto exit;

		goto exit_free_skb;
	}

	target->sel_res = sel_res;

	if (DIGITAL_SEL_RES_IS_T2T(sel_res)) {
		nfc_proto = NFC_PROTO_MIFARE;
	} else if (DIGITAL_SEL_RES_IS_NFC_DEP(sel_res)) {
		nfc_proto = NFC_PROTO_NFC_DEP;
	} else if (DIGITAL_SEL_RES_IS_T4T(sel_res)) {
		rc = digital_in_send_rats(ddev, target);
		if (rc)
			goto exit;
		/*
		 * Skip target_found and don't free it for now. This will be
		 * done when receiving the ATS
		 */
		goto exit_free_skb;
	} else {
		rc = -EOPNOTSUPP;
		goto exit;
	}

	rc = digital_target_found(ddev, target, nfc_proto);

exit:
	kfree(target);

exit_free_skb:
	dev_kfree_skb(resp);

	if (rc)
		digital_poll_next_tech(ddev);
}