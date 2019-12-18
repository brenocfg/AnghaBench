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
struct tcphdr {scalar_t__ rst; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int frag_off; scalar_t__ protocol; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  IP_OFFSET ; 
 int htons (int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_hdrlen (struct sk_buff*) ; 
 scalar_t__ nf_ip_checksum (struct sk_buff*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,struct tcphdr*) ; 

const struct tcphdr *nf_reject_ip_tcphdr_get(struct sk_buff *oldskb,
					     struct tcphdr *_oth, int hook)
{
	const struct tcphdr *oth;

	/* IP header checks: fragment. */
	if (ip_hdr(oldskb)->frag_off & htons(IP_OFFSET))
		return NULL;

	if (ip_hdr(oldskb)->protocol != IPPROTO_TCP)
		return NULL;

	oth = skb_header_pointer(oldskb, ip_hdrlen(oldskb),
				 sizeof(struct tcphdr), _oth);
	if (oth == NULL)
		return NULL;

	/* No RST for RST. */
	if (oth->rst)
		return NULL;

	/* Check checksum */
	if (nf_ip_checksum(oldskb, hook, ip_hdrlen(oldskb), IPPROTO_TCP))
		return NULL;

	return oth;
}