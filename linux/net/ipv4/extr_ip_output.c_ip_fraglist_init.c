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
struct sk_buff {unsigned int len; scalar_t__ data_len; } ;
struct iphdr {void* frag_off; void* tot_len; } ;
struct ip_fraglist_iter {unsigned int hlen; struct iphdr* iph; scalar_t__ offset; int /*<<< orphan*/  frag; } ;
struct TYPE_2__ {int /*<<< orphan*/  frag_list; } ;

/* Variables and functions */
 unsigned int IP_MF ; 
 void* htons (unsigned int) ; 
 int /*<<< orphan*/  ip_send_check (struct iphdr*) ; 
 int /*<<< orphan*/  skb_frag_list_init (struct sk_buff*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 unsigned int skb_pagelen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

void ip_fraglist_init(struct sk_buff *skb, struct iphdr *iph,
		      unsigned int hlen, struct ip_fraglist_iter *iter)
{
	unsigned int first_len = skb_pagelen(skb);

	iter->frag = skb_shinfo(skb)->frag_list;
	skb_frag_list_init(skb);

	iter->offset = 0;
	iter->iph = iph;
	iter->hlen = hlen;

	skb->data_len = first_len - skb_headlen(skb);
	skb->len = first_len;
	iph->tot_len = htons(first_len);
	iph->frag_off = htons(IP_MF);
	ip_send_check(iph);
}