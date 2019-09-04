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
struct sk_buff {scalar_t__ data; } ;
struct nfc_digital_dev {int dummy; } ;
struct digital_sdd_res {int* nfcid1; int bcc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NFC_DIGITAL_CONFIG_FRAMING ; 
 int /*<<< orphan*/  NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A ; 
 struct sk_buff* digital_skb_alloc (struct nfc_digital_dev*,int) ; 
 int digital_tg_configure_hw (struct nfc_digital_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digital_tg_recv_sel_req ; 
 int digital_tg_send_cmd (struct nfc_digital_dev*,struct sk_buff*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int digital_tg_send_sdd_res(struct nfc_digital_dev *ddev)
{
	struct sk_buff *skb;
	struct digital_sdd_res *sdd_res;
	int rc, i;

	skb = digital_skb_alloc(ddev, sizeof(struct digital_sdd_res));
	if (!skb)
		return -ENOMEM;

	skb_put(skb, sizeof(struct digital_sdd_res));
	sdd_res = (struct digital_sdd_res *)skb->data;

	sdd_res->nfcid1[0] = 0x08;
	get_random_bytes(sdd_res->nfcid1 + 1, 3);

	sdd_res->bcc = 0;
	for (i = 0; i < 4; i++)
		sdd_res->bcc ^= sdd_res->nfcid1[i];

	rc = digital_tg_configure_hw(ddev, NFC_DIGITAL_CONFIG_FRAMING,
				NFC_DIGITAL_FRAMING_NFCA_STANDARD_WITH_CRC_A);
	if (rc) {
		kfree_skb(skb);
		return rc;
	}

	rc = digital_tg_send_cmd(ddev, skb, 300, digital_tg_recv_sel_req,
				 NULL);
	if (rc)
		kfree_skb(skb);

	return rc;
}