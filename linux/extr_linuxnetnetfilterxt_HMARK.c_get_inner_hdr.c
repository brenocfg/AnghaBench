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
struct icmphdr {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  _ih ;

/* Variables and functions */
 scalar_t__ ICMP_DEST_UNREACH ; 
 scalar_t__ ICMP_PARAMETERPROB ; 
 scalar_t__ ICMP_REDIRECT ; 
 scalar_t__ ICMP_SOURCE_QUENCH ; 
 scalar_t__ ICMP_TIME_EXCEEDED ; 
 scalar_t__ NR_ICMP_TYPES ; 
 struct icmphdr* skb_header_pointer (struct sk_buff const*,int,int,struct icmphdr*) ; 

__attribute__((used)) static int get_inner_hdr(const struct sk_buff *skb, int iphsz, int *nhoff)
{
	const struct icmphdr *icmph;
	struct icmphdr _ih;

	/* Not enough header? */
	icmph = skb_header_pointer(skb, *nhoff + iphsz, sizeof(_ih), &_ih);
	if (icmph == NULL || icmph->type > NR_ICMP_TYPES)
		return 0;

	/* Error message? */
	if (icmph->type != ICMP_DEST_UNREACH &&
	    icmph->type != ICMP_SOURCE_QUENCH &&
	    icmph->type != ICMP_TIME_EXCEEDED &&
	    icmph->type != ICMP_PARAMETERPROB &&
	    icmph->type != ICMP_REDIRECT)
		return 0;

	*nhoff += iphsz + sizeof(_ih);
	return 1;
}