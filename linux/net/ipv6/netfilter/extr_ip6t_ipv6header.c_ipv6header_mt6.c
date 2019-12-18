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
typedef  int u8 ;
struct xt_action_param {int hotdrop; struct ip6t_ipv6header_info* matchinfo; } ;
struct sk_buff {unsigned int len; } ;
struct ipv6hdr {int dummy; } ;
struct ipv6_opt_hdr {int nexthdr; } ;
struct ip6t_ipv6header_info {unsigned int matchflags; unsigned int invflags; scalar_t__ modeflag; } ;
typedef  int /*<<< orphan*/  _hdr ;
struct TYPE_2__ {int nexthdr; } ;

/* Variables and functions */
 unsigned int MASK_AH ; 
 unsigned int MASK_DSTOPTS ; 
 unsigned int MASK_ESP ; 
 unsigned int MASK_FRAGMENT ; 
 unsigned int MASK_HOPOPTS ; 
 unsigned int MASK_NONE ; 
 unsigned int MASK_PROTO ; 
 unsigned int MASK_ROUTING ; 
#define  NEXTHDR_AUTH 132 
#define  NEXTHDR_DEST 131 
 int NEXTHDR_ESP ; 
#define  NEXTHDR_FRAGMENT 130 
#define  NEXTHDR_HOP 129 
 int NEXTHDR_NONE ; 
#define  NEXTHDR_ROUTING 128 
 int ipv6_authlen (struct ipv6_opt_hdr const*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff const*) ; 
 int ipv6_optlen (struct ipv6_opt_hdr const*) ; 
 scalar_t__ nf_ip6_ext_hdr (int) ; 
 struct ipv6_opt_hdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct ipv6_opt_hdr*) ; 

__attribute__((used)) static bool
ipv6header_mt6(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct ip6t_ipv6header_info *info = par->matchinfo;
	unsigned int temp;
	int len;
	u8 nexthdr;
	unsigned int ptr;

	/* Make sure this isn't an evil packet */

	/* type of the 1st exthdr */
	nexthdr = ipv6_hdr(skb)->nexthdr;
	/* pointer to the 1st exthdr */
	ptr = sizeof(struct ipv6hdr);
	/* available length */
	len = skb->len - ptr;
	temp = 0;

	while (nf_ip6_ext_hdr(nexthdr)) {
		const struct ipv6_opt_hdr *hp;
		struct ipv6_opt_hdr _hdr;
		int hdrlen;

		/* No more exthdr -> evaluate */
		if (nexthdr == NEXTHDR_NONE) {
			temp |= MASK_NONE;
			break;
		}
		/* Is there enough space for the next ext header? */
		if (len < (int)sizeof(struct ipv6_opt_hdr))
			return false;
		/* ESP -> evaluate */
		if (nexthdr == NEXTHDR_ESP) {
			temp |= MASK_ESP;
			break;
		}

		hp = skb_header_pointer(skb, ptr, sizeof(_hdr), &_hdr);
		if (!hp) {
			par->hotdrop = true;
			return false;
		}

		/* Calculate the header length */
		if (nexthdr == NEXTHDR_FRAGMENT)
			hdrlen = 8;
		else if (nexthdr == NEXTHDR_AUTH)
			hdrlen = ipv6_authlen(hp);
		else
			hdrlen = ipv6_optlen(hp);

		/* set the flag */
		switch (nexthdr) {
		case NEXTHDR_HOP:
			temp |= MASK_HOPOPTS;
			break;
		case NEXTHDR_ROUTING:
			temp |= MASK_ROUTING;
			break;
		case NEXTHDR_FRAGMENT:
			temp |= MASK_FRAGMENT;
			break;
		case NEXTHDR_AUTH:
			temp |= MASK_AH;
			break;
		case NEXTHDR_DEST:
			temp |= MASK_DSTOPTS;
			break;
		default:
			return false;
		}

		nexthdr = hp->nexthdr;
		len -= hdrlen;
		ptr += hdrlen;
		if (ptr > skb->len)
			break;
	}

	if (nexthdr != NEXTHDR_NONE && nexthdr != NEXTHDR_ESP)
		temp |= MASK_PROTO;

	if (info->modeflag)
		return !((temp ^ info->matchflags ^ info->invflags)
			 & info->matchflags);
	else {
		if (info->invflags)
			return temp != info->matchflags;
		else
			return temp == info->matchflags;
	}
}