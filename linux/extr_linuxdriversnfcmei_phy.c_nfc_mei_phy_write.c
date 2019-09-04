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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nfc_mei_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEI_DUMP_SKB_OUT (char*,struct sk_buff*) ; 
 int mei_nfc_send (struct nfc_mei_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfc_mei_phy_write(void *phy_id, struct sk_buff *skb)
{
	struct nfc_mei_phy *phy = phy_id;
	int r;

	MEI_DUMP_SKB_OUT("mei frame sent", skb);

	r = mei_nfc_send(phy, skb->data, skb->len);
	if (r > 0)
		r = 0;

	return r;
}