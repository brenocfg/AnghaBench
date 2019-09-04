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
struct ipv6hdr {int nexthdr; } ;
struct ipv6_rt_hdr {int dummy; } ;
struct ipv6_opt_hdr {int nexthdr; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NEXTHDR_DEST 130 
#define  NEXTHDR_HOP 129 
#define  NEXTHDR_ROUTING 128 
 int XFRM_POLICY_OUT ; 
 int /*<<< orphan*/  ipv6_optlen (struct ipv6_opt_hdr*) ; 
 int /*<<< orphan*/  ipv6_rearrange_destopt (struct ipv6hdr*,struct ipv6_opt_hdr*) ; 
 int /*<<< orphan*/  ipv6_rearrange_rthdr (struct ipv6hdr*,struct ipv6_rt_hdr*) ; 
 int /*<<< orphan*/  net_dbg_ratelimited (char*,char*) ; 
 int /*<<< orphan*/  zero_out_mutable_opts (struct ipv6_opt_hdr*) ; 

__attribute__((used)) static int ipv6_clear_mutable_options(struct ipv6hdr *iph, int len, int dir)
{
	union {
		struct ipv6hdr *iph;
		struct ipv6_opt_hdr *opth;
		struct ipv6_rt_hdr *rth;
		char *raw;
	} exthdr = { .iph = iph };
	char *end = exthdr.raw + len;
	int nexthdr = iph->nexthdr;

	exthdr.iph++;

	while (exthdr.raw < end) {
		switch (nexthdr) {
		case NEXTHDR_DEST:
			if (dir == XFRM_POLICY_OUT)
				ipv6_rearrange_destopt(iph, exthdr.opth);
			/* fall through */
		case NEXTHDR_HOP:
			if (!zero_out_mutable_opts(exthdr.opth)) {
				net_dbg_ratelimited("overrun %sopts\n",
						    nexthdr == NEXTHDR_HOP ?
						    "hop" : "dest");
				return -EINVAL;
			}
			break;

		case NEXTHDR_ROUTING:
			ipv6_rearrange_rthdr(iph, exthdr.rth);
			break;

		default:
			return 0;
		}

		nexthdr = exthdr.opth->nexthdr;
		exthdr.raw += ipv6_optlen(exthdr.opth);
	}

	return 0;
}