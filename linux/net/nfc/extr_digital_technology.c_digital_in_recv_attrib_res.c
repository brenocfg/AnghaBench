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
struct nfc_target {int dummy; } ;
struct nfc_digital_dev {int dummy; } ;
struct digital_attrib_res {int mbli_did; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  NFC_PROTO_ISO14443_B ; 
 int /*<<< orphan*/  PROTOCOL_ERR (char*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  digital_poll_next_tech (struct nfc_digital_dev*) ; 
 int digital_target_found (struct nfc_digital_dev*,struct nfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfc_target*) ; 

__attribute__((used)) static void digital_in_recv_attrib_res(struct nfc_digital_dev *ddev, void *arg,
				       struct sk_buff *resp)
{
	struct nfc_target *target = arg;
	struct digital_attrib_res *attrib_res;
	int rc;

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);
		resp = NULL;
		goto exit;
	}

	if (resp->len < sizeof(*attrib_res)) {
		PROTOCOL_ERR("12.6.2");
		rc = -EIO;
		goto exit;
	}

	attrib_res = (struct digital_attrib_res *)resp->data;

	if (attrib_res->mbli_did & 0x0f) {
		PROTOCOL_ERR("12.6.2.1");
		rc = -EIO;
		goto exit;
	}

	rc = digital_target_found(ddev, target, NFC_PROTO_ISO14443_B);

exit:
	dev_kfree_skb(resp);
	kfree(target);

	if (rc)
		digital_poll_next_tech(ddev);
}