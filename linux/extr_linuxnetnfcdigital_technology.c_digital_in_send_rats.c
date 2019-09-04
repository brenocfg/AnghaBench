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
struct nfc_target {int dummy; } ;
struct nfc_digital_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIGITAL_RATS_BYTE1 ; 
 int /*<<< orphan*/  DIGITAL_RATS_PARAM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  digital_in_recv_ats ; 
 int digital_in_send_cmd (struct nfc_digital_dev*,struct sk_buff*,int,int /*<<< orphan*/ ,struct nfc_target*) ; 
 struct sk_buff* digital_skb_alloc (struct nfc_digital_dev*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_u8 (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int digital_in_send_rats(struct nfc_digital_dev *ddev,
				struct nfc_target *target)
{
	int rc;
	struct sk_buff *skb;

	skb = digital_skb_alloc(ddev, 2);
	if (!skb)
		return -ENOMEM;

	skb_put_u8(skb, DIGITAL_RATS_BYTE1);
	skb_put_u8(skb, DIGITAL_RATS_PARAM);

	rc = digital_in_send_cmd(ddev, skb, 30, digital_in_recv_ats,
				 target);
	if (rc)
		kfree_skb(skb);

	return rc;
}