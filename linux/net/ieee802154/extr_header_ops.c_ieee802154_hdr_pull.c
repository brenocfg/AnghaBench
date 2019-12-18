#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {scalar_t__ security_enabled; } ;
struct ieee802154_hdr {int /*<<< orphan*/  sec; TYPE_1__ fc; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ieee802154_hdr_get_addrs (int /*<<< orphan*/ *,struct ieee802154_hdr*) ; 
 scalar_t__ ieee802154_hdr_get_sechdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ieee802154_hdr_minlen (struct ieee802154_hdr*) ; 
 int ieee802154_hdr_sechdr_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ieee802154_hdr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

int
ieee802154_hdr_pull(struct sk_buff *skb, struct ieee802154_hdr *hdr)
{
	int pos = 3, rc;

	if (!pskb_may_pull(skb, 3))
		return -EINVAL;

	memcpy(hdr, skb->data, 3);

	rc = ieee802154_hdr_minlen(hdr);
	if (rc < 0 || !pskb_may_pull(skb, rc))
		return -EINVAL;

	pos += ieee802154_hdr_get_addrs(skb->data + pos, hdr);

	if (hdr->fc.security_enabled) {
		int want = pos + ieee802154_hdr_sechdr_len(skb->data[pos]);

		if (!pskb_may_pull(skb, want))
			return -EINVAL;

		pos += ieee802154_hdr_get_sechdr(skb->data + pos, &hdr->sec);
	}

	skb_pull(skb, pos);
	return pos;
}