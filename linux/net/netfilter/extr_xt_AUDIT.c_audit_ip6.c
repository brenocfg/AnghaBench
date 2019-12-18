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
struct ipv6hdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  nexthdr; } ;
struct audit_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  _ip6h ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_skip_exthdr (struct sk_buff*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ipv6hdr* skb_header_pointer (struct sk_buff*,scalar_t__,int,struct ipv6hdr*) ; 
 scalar_t__ skb_network_offset (struct sk_buff*) ; 

__attribute__((used)) static bool audit_ip6(struct audit_buffer *ab, struct sk_buff *skb)
{
	struct ipv6hdr _ip6h;
	const struct ipv6hdr *ih;
	u8 nexthdr;
	__be16 frag_off;

	ih = skb_header_pointer(skb, skb_network_offset(skb), sizeof(_ip6h), &_ip6h);
	if (!ih)
		return false;

	nexthdr = ih->nexthdr;
	ipv6_skip_exthdr(skb, skb_network_offset(skb) + sizeof(_ip6h), &nexthdr, &frag_off);

	audit_log_format(ab, " saddr=%pI6c daddr=%pI6c proto=%hhu",
			 &ih->saddr, &ih->daddr, nexthdr);

	return true;
}