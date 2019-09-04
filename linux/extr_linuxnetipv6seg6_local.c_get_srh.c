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
struct sk_buff {scalar_t__ data; } ;
struct ipv6_sr_hdr {int hdrlen; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_ROUTING ; 
 scalar_t__ ipv6_find_hdr (struct sk_buff*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  seg6_validate_srh (struct ipv6_sr_hdr*,int) ; 

__attribute__((used)) static struct ipv6_sr_hdr *get_srh(struct sk_buff *skb)
{
	struct ipv6_sr_hdr *srh;
	int len, srhoff = 0;

	if (ipv6_find_hdr(skb, &srhoff, IPPROTO_ROUTING, NULL, NULL) < 0)
		return NULL;

	if (!pskb_may_pull(skb, srhoff + sizeof(*srh)))
		return NULL;

	srh = (struct ipv6_sr_hdr *)(skb->data + srhoff);

	len = (srh->hdrlen + 1) << 3;

	if (!pskb_may_pull(skb, srhoff + len))
		return NULL;

	if (!seg6_validate_srh(srh, len))
		return NULL;

	return srh;
}