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
struct nfc_digital_dev {scalar_t__ curr_nfc_dep_pni; int /*<<< orphan*/  (* skb_add_crc ) (struct sk_buff*) ;int /*<<< orphan*/  local_payload_max; int /*<<< orphan*/  nfc_dev; } ;
struct digital_atr_res {int /*<<< orphan*/  gb; int /*<<< orphan*/  pp; int /*<<< orphan*/  to; int /*<<< orphan*/  nfcid3; int /*<<< orphan*/  cmd; int /*<<< orphan*/  dir; } ;
struct digital_atr_req {int /*<<< orphan*/ * nfcid3; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_CMD_ATR_RES ; 
 int /*<<< orphan*/  DIGITAL_GB_BIT ; 
 int /*<<< orphan*/  DIGITAL_NFC_DEP_FRAME_DIR_IN ; 
 int /*<<< orphan*/  DIGITAL_NFC_DEP_TG_MAX_WT ; 
 int /*<<< orphan*/  DIGITAL_PAYLOAD_BITS_TO_PP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIGITAL_PAYLOAD_SIZE_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  digital_payload_size_to_bits (int /*<<< orphan*/ ) ; 
 struct sk_buff* digital_skb_alloc (struct nfc_digital_dev*,int) ; 
 int /*<<< orphan*/  digital_skb_push_dep_sod (struct nfc_digital_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  digital_tg_send_atr_res_complete ; 
 int digital_tg_send_cmd (struct nfc_digital_dev*,struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (struct digital_atr_res*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * nfc_get_local_general_bytes (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 

__attribute__((used)) static int digital_tg_send_atr_res(struct nfc_digital_dev *ddev,
				   struct digital_atr_req *atr_req)
{
	struct digital_atr_res *atr_res;
	struct sk_buff *skb;
	u8 *gb, payload_bits;
	size_t gb_len;
	int rc;

	gb = nfc_get_local_general_bytes(ddev->nfc_dev, &gb_len);
	if (!gb)
		gb_len = 0;

	skb = digital_skb_alloc(ddev, sizeof(struct digital_atr_res) + gb_len);
	if (!skb)
		return -ENOMEM;

	skb_put(skb, sizeof(struct digital_atr_res));
	atr_res = (struct digital_atr_res *)skb->data;

	memset(atr_res, 0, sizeof(struct digital_atr_res));

	atr_res->dir = DIGITAL_NFC_DEP_FRAME_DIR_IN;
	atr_res->cmd = DIGITAL_CMD_ATR_RES;
	memcpy(atr_res->nfcid3, atr_req->nfcid3, sizeof(atr_req->nfcid3));
	atr_res->to = DIGITAL_NFC_DEP_TG_MAX_WT;

	ddev->local_payload_max = DIGITAL_PAYLOAD_SIZE_MAX;
	payload_bits = digital_payload_size_to_bits(ddev->local_payload_max);
	atr_res->pp = DIGITAL_PAYLOAD_BITS_TO_PP(payload_bits);

	if (gb_len) {
		skb_put(skb, gb_len);

		atr_res->pp |= DIGITAL_GB_BIT;
		memcpy(atr_res->gb, gb, gb_len);
	}

	digital_skb_push_dep_sod(ddev, skb);

	ddev->skb_add_crc(skb);

	ddev->curr_nfc_dep_pni = 0;

	rc = digital_tg_send_cmd(ddev, skb, 999,
				 digital_tg_send_atr_res_complete, NULL);
	if (rc)
		kfree_skb(skb);

	return rc;
}