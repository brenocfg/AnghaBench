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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct nfc_target {int /*<<< orphan*/  sens_res; } ;
struct nfc_digital_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ DIGITAL_SENS_RES_IS_T1T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIGITAL_SENS_RES_IS_VALID (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  NFC_PROTO_JEWEL ; 
 int /*<<< orphan*/  PROTOCOL_ERR (char*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int digital_in_send_sdd_req (struct nfc_digital_dev*,struct nfc_target*) ; 
 int /*<<< orphan*/  digital_poll_next_tech (struct nfc_digital_dev*) ; 
 int digital_target_found (struct nfc_digital_dev*,struct nfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfc_target*) ; 
 struct nfc_target* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void digital_in_recv_sens_res(struct nfc_digital_dev *ddev, void *arg,
				     struct sk_buff *resp)
{
	struct nfc_target *target = NULL;
	int rc;

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);
		resp = NULL;
		goto exit;
	}

	if (resp->len < sizeof(u16)) {
		rc = -EIO;
		goto exit;
	}

	target = kzalloc(sizeof(struct nfc_target), GFP_KERNEL);
	if (!target) {
		rc = -ENOMEM;
		goto exit;
	}

	target->sens_res = __le16_to_cpu(*(__le16 *)resp->data);

	if (!DIGITAL_SENS_RES_IS_VALID(target->sens_res)) {
		PROTOCOL_ERR("4.6.3.3");
		rc = -EINVAL;
		goto exit;
	}

	if (DIGITAL_SENS_RES_IS_T1T(target->sens_res))
		rc = digital_target_found(ddev, target, NFC_PROTO_JEWEL);
	else
		rc = digital_in_send_sdd_req(ddev, target);

exit:
	dev_kfree_skb(resp);

	if (rc) {
		kfree(target);
		digital_poll_next_tech(ddev);
	}
}