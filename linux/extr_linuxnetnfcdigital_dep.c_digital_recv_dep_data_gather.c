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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct nfc_digital_dev {int local_payload_max; struct sk_buff* chaining_skb; } ;
struct digital_data_exch {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIGITAL_NFC_DEP_MI_BIT_SET (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nfc_alloc_recv_skb (int,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headroom (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *
digital_recv_dep_data_gather(struct nfc_digital_dev *ddev, u8 pfb,
			     struct sk_buff *resp,
			     int (*send_ack)(struct nfc_digital_dev *ddev,
					     struct digital_data_exch
							     *data_exch),
			     struct digital_data_exch *data_exch)
{
	struct sk_buff *new_skb;
	int rc;

	if (DIGITAL_NFC_DEP_MI_BIT_SET(pfb) && (!ddev->chaining_skb)) {
		ddev->chaining_skb =
			nfc_alloc_recv_skb(8 * ddev->local_payload_max,
					   GFP_KERNEL);
		if (!ddev->chaining_skb) {
			rc = -ENOMEM;
			goto error;
		}
	}

	if (ddev->chaining_skb) {
		if (resp->len > skb_tailroom(ddev->chaining_skb)) {
			new_skb = skb_copy_expand(ddev->chaining_skb,
						  skb_headroom(
							  ddev->chaining_skb),
						  8 * ddev->local_payload_max,
						  GFP_KERNEL);
			if (!new_skb) {
				rc = -ENOMEM;
				goto error;
			}

			kfree_skb(ddev->chaining_skb);
			ddev->chaining_skb = new_skb;
		}

		skb_put_data(ddev->chaining_skb, resp->data, resp->len);

		kfree_skb(resp);
		resp = NULL;

		if (DIGITAL_NFC_DEP_MI_BIT_SET(pfb)) {
			rc = send_ack(ddev, data_exch);
			if (rc)
				goto error;

			return NULL;
		}

		resp = ddev->chaining_skb;
		ddev->chaining_skb = NULL;
	}

	return resp;

error:
	kfree_skb(resp);

	kfree_skb(ddev->chaining_skb);
	ddev->chaining_skb = NULL;

	return ERR_PTR(rc);
}