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
struct net {int dummy; } ;
struct iphdr {int ihl; } ;
struct ip_options {int optlen; int is_strictroute; int /*<<< orphan*/  router_alert; int /*<<< orphan*/  rr; int /*<<< orphan*/  srr; int /*<<< orphan*/  __data; } ;
typedef  int /*<<< orphan*/  _iph ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EBADMSG ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
#define  IPOPT_LSRR 131 
#define  IPOPT_RA 130 
#define  IPOPT_RR 129 
#define  IPOPT_SSRR 128 
 scalar_t__ __ip_options_compile (struct net*,struct ip_options*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ip_options*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,unsigned int,int /*<<< orphan*/ ,int) ; 
 struct iphdr* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,struct iphdr*) ; 

__attribute__((used)) static int ipv4_find_option(struct net *net, struct sk_buff *skb,
			    unsigned int *offset, int target)
{
	unsigned char optbuf[sizeof(struct ip_options) + 40];
	struct ip_options *opt = (struct ip_options *)optbuf;
	struct iphdr *iph, _iph;
	unsigned int start;
	bool found = false;
	__be32 info;
	int optlen;

	iph = skb_header_pointer(skb, 0, sizeof(_iph), &_iph);
	if (!iph)
		return -EBADMSG;
	start = sizeof(struct iphdr);

	optlen = iph->ihl * 4 - (int)sizeof(struct iphdr);
	if (optlen <= 0)
		return -ENOENT;

	memset(opt, 0, sizeof(struct ip_options));
	/* Copy the options since __ip_options_compile() modifies
	 * the options.
	 */
	if (skb_copy_bits(skb, start, opt->__data, optlen))
		return -EBADMSG;
	opt->optlen = optlen;

	if (__ip_options_compile(net, opt, NULL, &info))
		return -EBADMSG;

	switch (target) {
	case IPOPT_SSRR:
	case IPOPT_LSRR:
		if (!opt->srr)
			break;
		found = target == IPOPT_SSRR ? opt->is_strictroute :
					       !opt->is_strictroute;
		if (found)
			*offset = opt->srr + start;
		break;
	case IPOPT_RR:
		if (!opt->rr)
			break;
		*offset = opt->rr + start;
		found = true;
		break;
	case IPOPT_RA:
		if (!opt->router_alert)
			break;
		*offset = opt->router_alert + start;
		found = true;
		break;
	default:
		return -EOPNOTSUPP;
	}
	return found ? target : -ENOENT;
}