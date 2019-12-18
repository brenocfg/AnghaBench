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
struct rtable {int dummy; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct iphdr {int dummy; } ;
struct ip_options {unsigned char* __data; int optlen; int is_changed; int srr; unsigned char faddr; int is_strictroute; int rr; int rr_needaddr; int ts; int ts_needtime; int ts_needaddr; int router_alert; int cipso; } ;
typedef  unsigned char __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_RAW ; 
 int EINVAL ; 
 int INADDR_ANY ; 
#define  IPOPT_CIPSO 140 
#define  IPOPT_END 139 
#define  IPOPT_LSRR 138 
#define  IPOPT_NOOP 137 
#define  IPOPT_RA 136 
#define  IPOPT_RR 135 
#define  IPOPT_SEC 134 
#define  IPOPT_SID 133 
#define  IPOPT_SSRR 132 
#define  IPOPT_TIMESTAMP 131 
#define  IPOPT_TS_PRESPEC 130 
#define  IPOPT_TS_TSANDADDR 129 
#define  IPOPT_TS_TSONLY 128 
 int /*<<< orphan*/  RTN_UNICAST ; 
 int /*<<< orphan*/  cipso_v4_validate (struct sk_buff*,unsigned char**) ; 
 unsigned char htonl (int) ; 
 int /*<<< orphan*/  inet_addr_type (struct net*,unsigned char) ; 
 unsigned char inet_current_timestamp () ; 
 int /*<<< orphan*/ * ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtable* skb_rtable (struct sk_buff*) ; 
 int /*<<< orphan*/  spec_dst_fill (unsigned char*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int __ip_options_compile(struct net *net,
			 struct ip_options *opt, struct sk_buff *skb,
			 __be32 *info)
{
	__be32 spec_dst = htonl(INADDR_ANY);
	unsigned char *pp_ptr = NULL;
	struct rtable *rt = NULL;
	unsigned char *optptr;
	unsigned char *iph;
	int optlen, l;

	if (skb) {
		rt = skb_rtable(skb);
		optptr = (unsigned char *)&(ip_hdr(skb)[1]);
	} else
		optptr = opt->__data;
	iph = optptr - sizeof(struct iphdr);

	for (l = opt->optlen; l > 0; ) {
		switch (*optptr) {
		case IPOPT_END:
			for (optptr++, l--; l > 0; optptr++, l--) {
				if (*optptr != IPOPT_END) {
					*optptr = IPOPT_END;
					opt->is_changed = 1;
				}
			}
			goto eol;
		case IPOPT_NOOP:
			l--;
			optptr++;
			continue;
		}
		if (unlikely(l < 2)) {
			pp_ptr = optptr;
			goto error;
		}
		optlen = optptr[1];
		if (optlen < 2 || optlen > l) {
			pp_ptr = optptr;
			goto error;
		}
		switch (*optptr) {
		case IPOPT_SSRR:
		case IPOPT_LSRR:
			if (optlen < 3) {
				pp_ptr = optptr + 1;
				goto error;
			}
			if (optptr[2] < 4) {
				pp_ptr = optptr + 2;
				goto error;
			}
			/* NB: cf RFC-1812 5.2.4.1 */
			if (opt->srr) {
				pp_ptr = optptr;
				goto error;
			}
			if (!skb) {
				if (optptr[2] != 4 || optlen < 7 || ((optlen-3) & 3)) {
					pp_ptr = optptr + 1;
					goto error;
				}
				memcpy(&opt->faddr, &optptr[3], 4);
				if (optlen > 7)
					memmove(&optptr[3], &optptr[7], optlen-7);
			}
			opt->is_strictroute = (optptr[0] == IPOPT_SSRR);
			opt->srr = optptr - iph;
			break;
		case IPOPT_RR:
			if (opt->rr) {
				pp_ptr = optptr;
				goto error;
			}
			if (optlen < 3) {
				pp_ptr = optptr + 1;
				goto error;
			}
			if (optptr[2] < 4) {
				pp_ptr = optptr + 2;
				goto error;
			}
			if (optptr[2] <= optlen) {
				if (optptr[2]+3 > optlen) {
					pp_ptr = optptr + 2;
					goto error;
				}
				if (rt) {
					spec_dst_fill(&spec_dst, skb);
					memcpy(&optptr[optptr[2]-1], &spec_dst, 4);
					opt->is_changed = 1;
				}
				optptr[2] += 4;
				opt->rr_needaddr = 1;
			}
			opt->rr = optptr - iph;
			break;
		case IPOPT_TIMESTAMP:
			if (opt->ts) {
				pp_ptr = optptr;
				goto error;
			}
			if (optlen < 4) {
				pp_ptr = optptr + 1;
				goto error;
			}
			if (optptr[2] < 5) {
				pp_ptr = optptr + 2;
				goto error;
			}
			if (optptr[2] <= optlen) {
				unsigned char *timeptr = NULL;
				if (optptr[2]+3 > optlen) {
					pp_ptr = optptr + 2;
					goto error;
				}
				switch (optptr[3]&0xF) {
				case IPOPT_TS_TSONLY:
					if (skb)
						timeptr = &optptr[optptr[2]-1];
					opt->ts_needtime = 1;
					optptr[2] += 4;
					break;
				case IPOPT_TS_TSANDADDR:
					if (optptr[2]+7 > optlen) {
						pp_ptr = optptr + 2;
						goto error;
					}
					if (rt)  {
						spec_dst_fill(&spec_dst, skb);
						memcpy(&optptr[optptr[2]-1], &spec_dst, 4);
						timeptr = &optptr[optptr[2]+3];
					}
					opt->ts_needaddr = 1;
					opt->ts_needtime = 1;
					optptr[2] += 8;
					break;
				case IPOPT_TS_PRESPEC:
					if (optptr[2]+7 > optlen) {
						pp_ptr = optptr + 2;
						goto error;
					}
					{
						__be32 addr;
						memcpy(&addr, &optptr[optptr[2]-1], 4);
						if (inet_addr_type(net, addr) == RTN_UNICAST)
							break;
						if (skb)
							timeptr = &optptr[optptr[2]+3];
					}
					opt->ts_needtime = 1;
					optptr[2] += 8;
					break;
				default:
					if (!skb && !ns_capable(net->user_ns, CAP_NET_RAW)) {
						pp_ptr = optptr + 3;
						goto error;
					}
					break;
				}
				if (timeptr) {
					__be32 midtime;

					midtime = inet_current_timestamp();
					memcpy(timeptr, &midtime, 4);
					opt->is_changed = 1;
				}
			} else if ((optptr[3]&0xF) != IPOPT_TS_PRESPEC) {
				unsigned int overflow = optptr[3]>>4;
				if (overflow == 15) {
					pp_ptr = optptr + 3;
					goto error;
				}
				if (skb) {
					optptr[3] = (optptr[3]&0xF)|((overflow+1)<<4);
					opt->is_changed = 1;
				}
			}
			opt->ts = optptr - iph;
			break;
		case IPOPT_RA:
			if (optlen < 4) {
				pp_ptr = optptr + 1;
				goto error;
			}
			if (optptr[2] == 0 && optptr[3] == 0)
				opt->router_alert = optptr - iph;
			break;
		case IPOPT_CIPSO:
			if ((!skb && !ns_capable(net->user_ns, CAP_NET_RAW)) || opt->cipso) {
				pp_ptr = optptr;
				goto error;
			}
			opt->cipso = optptr - iph;
			if (cipso_v4_validate(skb, &optptr)) {
				pp_ptr = optptr;
				goto error;
			}
			break;
		case IPOPT_SEC:
		case IPOPT_SID:
		default:
			if (!skb && !ns_capable(net->user_ns, CAP_NET_RAW)) {
				pp_ptr = optptr;
				goto error;
			}
			break;
		}
		l -= optlen;
		optptr += optlen;
	}

eol:
	if (!pp_ptr)
		return 0;

error:
	if (info)
		*info = htonl((pp_ptr-iph)<<24);
	return -EINVAL;
}