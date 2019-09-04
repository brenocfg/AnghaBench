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
struct digital_sensf_req {int sc1; int sc2; scalar_t__ tsn; int /*<<< orphan*/  rc; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_CMD_SENSF_REQ ; 
 int /*<<< orphan*/  DIGITAL_DRV_CAPS_IN_CRC (struct nfc_digital_dev*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_FRAMING ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_RF_TECH ; 
 int NFC_DIGITAL_FRAMING_NFCF ; 
 int digital_in_configure_hw (struct nfc_digital_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  digital_in_recv_sensf_res ; 
 int digital_in_send_cmd (struct nfc_digital_dev*,struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  digital_skb_add_crc_f (struct sk_buff*) ; 
 struct sk_buff* digital_skb_alloc (struct nfc_digital_dev*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

int digital_in_send_sensf_req(struct nfc_digital_dev *ddev, u8 rf_tech)
{
	struct digital_sensf_req *sensf_req;
	struct sk_buff *skb;
	int rc;
	u8 size;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH, rf_tech);
	if (rc)
		return rc;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFCF);
	if (rc)
		return rc;

	size = sizeof(struct digital_sensf_req);

	skb = digital_skb_alloc(ddev, size);
	if (!skb)
		return -ENOMEM;

	skb_put(skb, size);

	sensf_req = (struct digital_sensf_req *)skb->data;
	sensf_req->cmd = DIGITAL_CMD_SENSF_REQ;
	sensf_req->sc1 = 0xFF;
	sensf_req->sc2 = 0xFF;
	sensf_req->rc = 0;
	sensf_req->tsn = 0;

	*(u8 *)skb_push(skb, 1) = size + 1;

	if (!DIGITAL_DRV_CAPS_IN_CRC(ddev))
		digital_skb_add_crc_f(skb);

	rc = digital_in_send_cmd(ddev, skb, 30, digital_in_recv_sensf_res,
				 NULL);
	if (rc)
		kfree_skb(skb);

	return rc;
}