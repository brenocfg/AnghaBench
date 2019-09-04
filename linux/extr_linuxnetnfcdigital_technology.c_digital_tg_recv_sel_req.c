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
struct sk_buff {int dummy; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_DRV_CAPS_TG_CRC (struct nfc_digital_dev*) ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  PROTOCOL_ERR (char*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  digital_poll_next_tech (struct nfc_digital_dev*) ; 
 int digital_skb_check_crc_a (struct sk_buff*) ; 
 int digital_tg_send_sel_res (struct nfc_digital_dev*) ; 

__attribute__((used)) static void digital_tg_recv_sel_req(struct nfc_digital_dev *ddev, void *arg,
				    struct sk_buff *resp)
{
	int rc;

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);
		resp = NULL;
		goto exit;
	}

	if (!DIGITAL_DRV_CAPS_TG_CRC(ddev)) {
		rc = digital_skb_check_crc_a(resp);
		if (rc) {
			PROTOCOL_ERR("4.4.1.3");
			goto exit;
		}
	}

	/* Silently ignore SEL_REQ content and send a SEL_RES for NFC-DEP */

	rc = digital_tg_send_sel_res(ddev);

exit:
	if (rc)
		digital_poll_next_tech(ddev);

	dev_kfree_skb(resp);
}