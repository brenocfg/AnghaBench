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
struct sk_buff {int dummy; } ;
struct nfc_digital_dev {int dummy; } ;
struct digital_sensb_req {int afi; int /*<<< orphan*/  param; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_CMD_SENSB_REQ ; 
 int /*<<< orphan*/  DIGITAL_SENSB_N (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_FRAMING ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_RF_TECH ; 
 int /*<<< orphan*/  NFC_DIGITAL_FRAMING_NFCB ; 
 int /*<<< orphan*/  NFC_DIGITAL_RF_TECH_106B ; 
 int digital_in_configure_hw (struct nfc_digital_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digital_in_recv_sensb_res ; 
 int digital_in_send_cmd (struct nfc_digital_dev*,struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct sk_buff* digital_skb_alloc (struct nfc_digital_dev*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct digital_sensb_req* skb_put (struct sk_buff*,int) ; 

int digital_in_send_sensb_req(struct nfc_digital_dev *ddev, u8 rf_tech)
{
	struct digital_sensb_req *sensb_req;
	struct sk_buff *skb;
	int rc;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_RF_TECH,
				     NFC_DIGITAL_RF_TECH_106B);
	if (rc)
		return rc;

	rc = digital_in_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				     NFC_DIGITAL_FRAMING_NFCB);
	if (rc)
		return rc;

	skb = digital_skb_alloc(ddev, sizeof(*sensb_req));
	if (!skb)
		return -ENOMEM;

	sensb_req = skb_put(skb, sizeof(*sensb_req));

	sensb_req->cmd = DIGITAL_CMD_SENSB_REQ;
	sensb_req->afi = 0x00; /* All families and sub-families */
	sensb_req->param = DIGITAL_SENSB_N(0);

	rc = digital_in_send_cmd(ddev, skb, 30, digital_in_recv_sensb_res,
				 NULL);
	if (rc)
		kfree_skb(skb);

	return rc;
}