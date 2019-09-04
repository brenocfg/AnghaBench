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
struct sk_buff {int dummy; } ;
struct ieee802154_hdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ieee802154_hdr_get_addrs (int /*<<< orphan*/  const*,struct ieee802154_hdr*) ; 
 int ieee802154_hdr_minlen (struct ieee802154_hdr*) ; 
 int /*<<< orphan*/  memcpy (struct ieee802154_hdr*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * skb_mac_header (struct sk_buff const*) ; 
 int /*<<< orphan*/  const* skb_tail_pointer (struct sk_buff const*) ; 

int
ieee802154_hdr_peek_addrs(const struct sk_buff *skb, struct ieee802154_hdr *hdr)
{
	const u8 *buf = skb_mac_header(skb);
	int pos = 3, rc;

	if (buf + 3 > skb_tail_pointer(skb))
		return -EINVAL;

	memcpy(hdr, buf, 3);

	rc = ieee802154_hdr_minlen(hdr);
	if (rc < 0 || buf + rc > skb_tail_pointer(skb))
		return -EINVAL;

	pos += ieee802154_hdr_get_addrs(buf + pos, hdr);
	return pos;
}