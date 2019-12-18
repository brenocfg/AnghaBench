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
struct nfc_target {int is_iso15693; int /*<<< orphan*/  iso15693_uid; int /*<<< orphan*/  iso15693_dsfid; } ;
struct nfc_digital_dev {int dummy; } ;
struct digital_iso15693_inv_res {int /*<<< orphan*/  uid; int /*<<< orphan*/  dsfid; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_ISO15693_RES_IS_VALID (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  NFC_PROTO_ISO15693 ; 
 int /*<<< orphan*/  PROTOCOL_ERR (char*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  digital_poll_next_tech (struct nfc_digital_dev*) ; 
 int digital_target_found (struct nfc_digital_dev*,struct nfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfc_target*) ; 
 struct nfc_target* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void digital_in_recv_iso15693_inv_res(struct nfc_digital_dev *ddev,
		void *arg, struct sk_buff *resp)
{
	struct digital_iso15693_inv_res *res;
	struct nfc_target *target = NULL;
	int rc;

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);
		resp = NULL;
		goto out_free_skb;
	}

	if (resp->len != sizeof(*res)) {
		rc = -EIO;
		goto out_free_skb;
	}

	res = (struct digital_iso15693_inv_res *)resp->data;

	if (!DIGITAL_ISO15693_RES_IS_VALID(res->flags)) {
		PROTOCOL_ERR("ISO15693 - 10.3.1");
		rc = -EINVAL;
		goto out_free_skb;
	}

	target = kzalloc(sizeof(*target), GFP_KERNEL);
	if (!target) {
		rc = -ENOMEM;
		goto out_free_skb;
	}

	target->is_iso15693 = 1;
	target->iso15693_dsfid = res->dsfid;
	memcpy(target->iso15693_uid, &res->uid, sizeof(target->iso15693_uid));

	rc = digital_target_found(ddev, target, NFC_PROTO_ISO15693);

	kfree(target);

out_free_skb:
	dev_kfree_skb(resp);

	if (rc)
		digital_poll_next_tech(ddev);
}