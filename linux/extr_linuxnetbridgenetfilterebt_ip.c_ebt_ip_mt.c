#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ code; } ;
struct TYPE_4__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
union pkthdr {scalar_t__ tos; int saddr; int daddr; scalar_t__ protocol; int ihl; TYPE_3__ igmphdr; TYPE_2__ icmphdr; TYPE_1__ tcpudphdr; int /*<<< orphan*/  frag_off; } ;
typedef  scalar_t__ u32 ;
struct xt_action_param {struct ebt_ip_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct iphdr {scalar_t__ tos; int saddr; int daddr; scalar_t__ protocol; int ihl; TYPE_3__ igmphdr; TYPE_2__ icmphdr; TYPE_1__ tcpudphdr; int /*<<< orphan*/  frag_off; } ;
struct ebt_ip_info {int bitmask; scalar_t__ tos; int smsk; int saddr; int dmsk; int daddr; scalar_t__ protocol; scalar_t__* dport; scalar_t__* sport; scalar_t__* icmp_type; scalar_t__* icmp_code; scalar_t__* igmp_type; } ;
typedef  int /*<<< orphan*/  _pkthdr ;
typedef  int /*<<< orphan*/  _iph ;

/* Variables and functions */
 int EBT_IP_DEST ; 
 int EBT_IP_DPORT ; 
 int EBT_IP_ICMP ; 
 int EBT_IP_IGMP ; 
 int EBT_IP_PROTO ; 
 int EBT_IP_SOURCE ; 
 int EBT_IP_SPORT ; 
 int EBT_IP_TOS ; 
 int IP_OFFSET ; 
 scalar_t__ NF_INVF (struct ebt_ip_info const*,int,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 union pkthdr* skb_header_pointer (struct sk_buff const*,int,int,union pkthdr*) ; 

__attribute__((used)) static bool
ebt_ip_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct ebt_ip_info *info = par->matchinfo;
	const struct iphdr *ih;
	struct iphdr _iph;
	const union pkthdr *pptr;
	union pkthdr _pkthdr;

	ih = skb_header_pointer(skb, 0, sizeof(_iph), &_iph);
	if (ih == NULL)
		return false;
	if ((info->bitmask & EBT_IP_TOS) &&
	    NF_INVF(info, EBT_IP_TOS, info->tos != ih->tos))
		return false;
	if ((info->bitmask & EBT_IP_SOURCE) &&
	    NF_INVF(info, EBT_IP_SOURCE,
		    (ih->saddr & info->smsk) != info->saddr))
		return false;
	if ((info->bitmask & EBT_IP_DEST) &&
	    NF_INVF(info, EBT_IP_DEST,
		    (ih->daddr & info->dmsk) != info->daddr))
		return false;
	if (info->bitmask & EBT_IP_PROTO) {
		if (NF_INVF(info, EBT_IP_PROTO, info->protocol != ih->protocol))
			return false;
		if (!(info->bitmask & (EBT_IP_DPORT | EBT_IP_SPORT |
				       EBT_IP_ICMP | EBT_IP_IGMP)))
			return true;
		if (ntohs(ih->frag_off) & IP_OFFSET)
			return false;

		/* min icmp/igmp headersize is 4, so sizeof(_pkthdr) is ok. */
		pptr = skb_header_pointer(skb, ih->ihl*4,
					  sizeof(_pkthdr), &_pkthdr);
		if (pptr == NULL)
			return false;
		if (info->bitmask & EBT_IP_DPORT) {
			u32 dst = ntohs(pptr->tcpudphdr.dst);
			if (NF_INVF(info, EBT_IP_DPORT,
				    dst < info->dport[0] ||
				    dst > info->dport[1]))
				return false;
		}
		if (info->bitmask & EBT_IP_SPORT) {
			u32 src = ntohs(pptr->tcpudphdr.src);
			if (NF_INVF(info, EBT_IP_SPORT,
				    src < info->sport[0] ||
				    src > info->sport[1]))
				return false;
		}
		if ((info->bitmask & EBT_IP_ICMP) &&
		    NF_INVF(info, EBT_IP_ICMP,
			    pptr->icmphdr.type < info->icmp_type[0] ||
			    pptr->icmphdr.type > info->icmp_type[1] ||
			    pptr->icmphdr.code < info->icmp_code[0] ||
			    pptr->icmphdr.code > info->icmp_code[1]))
			return false;
		if ((info->bitmask & EBT_IP_IGMP) &&
		    NF_INVF(info, EBT_IP_IGMP,
			    pptr->igmphdr.type < info->igmp_type[0] ||
			    pptr->igmphdr.type > info->igmp_type[1]))
			return false;
	}
	return true;
}