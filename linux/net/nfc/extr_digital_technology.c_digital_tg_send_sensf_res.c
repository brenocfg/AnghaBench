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
struct sk_buff {scalar_t__ data; } ;
struct nfc_digital_dev {int dummy; } ;
struct digital_sensf_res {int /*<<< orphan*/ * rd; int /*<<< orphan*/ * nfcid2; int /*<<< orphan*/  cmd; } ;
struct digital_sensf_req {int rc; int /*<<< orphan*/  sc2; int /*<<< orphan*/  sc1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_CMD_SENSF_RES ; 
 int /*<<< orphan*/  DIGITAL_DRV_CAPS_TG_CRC (struct nfc_digital_dev*) ; 
 int /*<<< orphan*/  DIGITAL_SENSF_NFCID2_NFC_DEP_B1 ; 
 int /*<<< orphan*/  DIGITAL_SENSF_NFCID2_NFC_DEP_B2 ; 
#define  DIGITAL_SENSF_REQ_RC_AP 129 
 int DIGITAL_SENSF_REQ_RC_NONE ; 
#define  DIGITAL_SENSF_REQ_RC_SC 128 
 int /*<<< orphan*/  DIGITAL_SENSF_RES_RD_AP_B1 ; 
 int /*<<< orphan*/  DIGITAL_SENSF_RES_RD_AP_B2 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  digital_skb_add_crc_f (struct sk_buff*) ; 
 struct sk_buff* digital_skb_alloc (struct nfc_digital_dev*,int) ; 
 int /*<<< orphan*/  digital_tg_recv_atr_or_sensf_req ; 
 int digital_tg_send_cmd (struct nfc_digital_dev*,struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct digital_sensf_res*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int digital_tg_send_sensf_res(struct nfc_digital_dev *ddev,
			      struct digital_sensf_req *sensf_req)
{
	struct sk_buff *skb;
	u8 size;
	int rc;
	struct digital_sensf_res *sensf_res;

	size = sizeof(struct digital_sensf_res);

	if (sensf_req->rc == DIGITAL_SENSF_REQ_RC_NONE)
		size -= sizeof(sensf_res->rd);

	skb = digital_skb_alloc(ddev, size);
	if (!skb)
		return -ENOMEM;

	skb_put(skb, size);

	sensf_res = (struct digital_sensf_res *)skb->data;

	memset(sensf_res, 0, size);

	sensf_res->cmd = DIGITAL_CMD_SENSF_RES;
	sensf_res->nfcid2[0] = DIGITAL_SENSF_NFCID2_NFC_DEP_B1;
	sensf_res->nfcid2[1] = DIGITAL_SENSF_NFCID2_NFC_DEP_B2;
	get_random_bytes(&sensf_res->nfcid2[2], 6);

	switch (sensf_req->rc) {
	case DIGITAL_SENSF_REQ_RC_SC:
		sensf_res->rd[0] = sensf_req->sc1;
		sensf_res->rd[1] = sensf_req->sc2;
		break;
	case DIGITAL_SENSF_REQ_RC_AP:
		sensf_res->rd[0] = DIGITAL_SENSF_RES_RD_AP_B1;
		sensf_res->rd[1] = DIGITAL_SENSF_RES_RD_AP_B2;
		break;
	}

	*(u8 *)skb_push(skb, sizeof(u8)) = size + 1;

	if (!DIGITAL_DRV_CAPS_TG_CRC(ddev))
		digital_skb_add_crc_f(skb);

	rc = digital_tg_send_cmd(ddev, skb, 300,
				 digital_tg_recv_atr_or_sensf_req, NULL);
	if (rc)
		kfree_skb(skb);

	return rc;
}