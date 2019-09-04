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
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct nfc_target {scalar_t__* sensf_res; scalar_t__ sensf_res_len; scalar_t__* nfcid2; scalar_t__ nfcid2_len; } ;
struct nfc_digital_dev {int dummy; } ;
struct digital_sensf_res {struct digital_sensf_res* nfcid2; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_DRV_CAPS_IN_CRC (struct nfc_digital_dev*) ; 
 scalar_t__ DIGITAL_SENSF_NFCID2_NFC_DEP_B1 ; 
 scalar_t__ DIGITAL_SENSF_NFCID2_NFC_DEP_B2 ; 
 scalar_t__ DIGITAL_SENSF_RES_MIN_LENGTH ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 scalar_t__ NFC_NFCID2_MAXSIZE ; 
 int /*<<< orphan*/  NFC_PROTO_FELICA ; 
 int /*<<< orphan*/  NFC_PROTO_NFC_DEP ; 
 int /*<<< orphan*/  PROTOCOL_ERR (char*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  digital_poll_next_tech (struct nfc_digital_dev*) ; 
 int digital_skb_check_crc_f (struct sk_buff*) ; 
 int digital_target_found (struct nfc_digital_dev*,struct nfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,struct digital_sensf_res*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct nfc_target*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static void digital_in_recv_sensf_res(struct nfc_digital_dev *ddev, void *arg,
				   struct sk_buff *resp)
{
	int rc;
	u8 proto;
	struct nfc_target target;
	struct digital_sensf_res *sensf_res;

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);
		resp = NULL;
		goto exit;
	}

	if (resp->len < DIGITAL_SENSF_RES_MIN_LENGTH) {
		rc = -EIO;
		goto exit;
	}

	if (!DIGITAL_DRV_CAPS_IN_CRC(ddev)) {
		rc = digital_skb_check_crc_f(resp);
		if (rc) {
			PROTOCOL_ERR("6.4.1.8");
			goto exit;
		}
	}

	skb_pull(resp, 1);

	memset(&target, 0, sizeof(struct nfc_target));

	sensf_res = (struct digital_sensf_res *)resp->data;

	memcpy(target.sensf_res, sensf_res, resp->len);
	target.sensf_res_len = resp->len;

	memcpy(target.nfcid2, sensf_res->nfcid2, NFC_NFCID2_MAXSIZE);
	target.nfcid2_len = NFC_NFCID2_MAXSIZE;

	if (target.nfcid2[0] == DIGITAL_SENSF_NFCID2_NFC_DEP_B1 &&
	    target.nfcid2[1] == DIGITAL_SENSF_NFCID2_NFC_DEP_B2)
		proto = NFC_PROTO_NFC_DEP;
	else
		proto = NFC_PROTO_FELICA;

	rc = digital_target_found(ddev, &target, proto);

exit:
	dev_kfree_skb(resp);

	if (rc)
		digital_poll_next_tech(ddev);
}