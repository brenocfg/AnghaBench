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
struct sk_buff {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct nfc_digital_dev {struct sk_buff* chaining_skb; struct digital_data_exch* data_exch; int /*<<< orphan*/  remote_payload_max; } ;
struct digital_dep_req_res {int /*<<< orphan*/  pfb; } ;
struct digital_data_exch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_NFC_DEP_PFB_MI_BIT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct sk_buff* digital_skb_alloc (struct nfc_digital_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
digital_send_dep_data_prep(struct nfc_digital_dev *ddev, struct sk_buff *skb,
			   struct digital_dep_req_res *dep_req_res,
			   struct digital_data_exch *data_exch)
{
	struct sk_buff *new_skb;

	if (skb->len > ddev->remote_payload_max) {
		dep_req_res->pfb |= DIGITAL_NFC_DEP_PFB_MI_BIT;

		new_skb = digital_skb_alloc(ddev, ddev->remote_payload_max);
		if (!new_skb) {
			kfree_skb(ddev->chaining_skb);
			ddev->chaining_skb = NULL;

			return ERR_PTR(-ENOMEM);
		}

		skb_put_data(new_skb, skb->data, ddev->remote_payload_max);
		skb_pull(skb, ddev->remote_payload_max);

		ddev->chaining_skb = skb;
		ddev->data_exch = data_exch;
	} else {
		ddev->chaining_skb = NULL;
		new_skb = skb;
	}

	return new_skb;
}