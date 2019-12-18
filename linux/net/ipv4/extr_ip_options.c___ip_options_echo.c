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
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip_options {scalar_t__ optlen; unsigned char* __data; int rr; int rr_needaddr; int ts; int ts_needaddr; int ts_needtime; int srr; unsigned char faddr; int cipso; int /*<<< orphan*/  is_strictroute; } ;
typedef  unsigned char __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPOPT_END ; 
 unsigned char IPOPT_TS_PRESPEC ; 
 scalar_t__ RTN_UNICAST ; 
 scalar_t__ inet_addr_type (struct net*,unsigned char) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (struct ip_options*,int /*<<< orphan*/ ,int) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 

int __ip_options_echo(struct net *net, struct ip_options *dopt,
		      struct sk_buff *skb, const struct ip_options *sopt)
{
	unsigned char *sptr, *dptr;
	int soffset, doffset;
	int	optlen;

	memset(dopt, 0, sizeof(struct ip_options));

	if (sopt->optlen == 0)
		return 0;

	sptr = skb_network_header(skb);
	dptr = dopt->__data;

	if (sopt->rr) {
		optlen  = sptr[sopt->rr+1];
		soffset = sptr[sopt->rr+2];
		dopt->rr = dopt->optlen + sizeof(struct iphdr);
		memcpy(dptr, sptr+sopt->rr, optlen);
		if (sopt->rr_needaddr && soffset <= optlen) {
			if (soffset + 3 > optlen)
				return -EINVAL;
			dptr[2] = soffset + 4;
			dopt->rr_needaddr = 1;
		}
		dptr += optlen;
		dopt->optlen += optlen;
	}
	if (sopt->ts) {
		optlen = sptr[sopt->ts+1];
		soffset = sptr[sopt->ts+2];
		dopt->ts = dopt->optlen + sizeof(struct iphdr);
		memcpy(dptr, sptr+sopt->ts, optlen);
		if (soffset <= optlen) {
			if (sopt->ts_needaddr) {
				if (soffset + 3 > optlen)
					return -EINVAL;
				dopt->ts_needaddr = 1;
				soffset += 4;
			}
			if (sopt->ts_needtime) {
				if (soffset + 3 > optlen)
					return -EINVAL;
				if ((dptr[3]&0xF) != IPOPT_TS_PRESPEC) {
					dopt->ts_needtime = 1;
					soffset += 4;
				} else {
					dopt->ts_needtime = 0;

					if (soffset + 7 <= optlen) {
						__be32 addr;

						memcpy(&addr, dptr+soffset-1, 4);
						if (inet_addr_type(net, addr) != RTN_UNICAST) {
							dopt->ts_needtime = 1;
							soffset += 8;
						}
					}
				}
			}
			dptr[2] = soffset;
		}
		dptr += optlen;
		dopt->optlen += optlen;
	}
	if (sopt->srr) {
		unsigned char *start = sptr+sopt->srr;
		__be32 faddr;

		optlen  = start[1];
		soffset = start[2];
		doffset = 0;
		if (soffset > optlen)
			soffset = optlen + 1;
		soffset -= 4;
		if (soffset > 3) {
			memcpy(&faddr, &start[soffset-1], 4);
			for (soffset -= 4, doffset = 4; soffset > 3; soffset -= 4, doffset += 4)
				memcpy(&dptr[doffset-1], &start[soffset-1], 4);
			/*
			 * RFC1812 requires to fix illegal source routes.
			 */
			if (memcmp(&ip_hdr(skb)->saddr,
				   &start[soffset + 3], 4) == 0)
				doffset -= 4;
		}
		if (doffset > 3) {
			dopt->faddr = faddr;
			dptr[0] = start[0];
			dptr[1] = doffset+3;
			dptr[2] = 4;
			dptr += doffset+3;
			dopt->srr = dopt->optlen + sizeof(struct iphdr);
			dopt->optlen += doffset+3;
			dopt->is_strictroute = sopt->is_strictroute;
		}
	}
	if (sopt->cipso) {
		optlen  = sptr[sopt->cipso+1];
		dopt->cipso = dopt->optlen+sizeof(struct iphdr);
		memcpy(dptr, sptr+sopt->cipso, optlen);
		dptr += optlen;
		dopt->optlen += optlen;
	}
	while (dopt->optlen & 3) {
		*dptr++ = IPOPT_END;
		dopt->optlen++;
	}
	return 0;
}