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
struct rtnexthop {int dummy; } ;
struct rtmsg {int dummy; } ;
struct fib_nh_common {scalar_t__ nhc_lwtstate; } ;
struct fib_info {scalar_t__ nh; } ;

/* Variables and functions */
 int NLMSG_ALIGN (int) ; 
 unsigned int RTAX_MAX ; 
 unsigned int TCP_CA_NAME_MAX ; 
 struct fib_nh_common* fib_info_nhc (struct fib_info*,unsigned int) ; 
 unsigned int fib_info_num_path (struct fib_info*) ; 
 scalar_t__ lwtunnel_get_encap_size (scalar_t__) ; 
 int nla_total_size (unsigned int) ; 

__attribute__((used)) static inline size_t fib_nlmsg_size(struct fib_info *fi)
{
	size_t payload = NLMSG_ALIGN(sizeof(struct rtmsg))
			 + nla_total_size(4) /* RTA_TABLE */
			 + nla_total_size(4) /* RTA_DST */
			 + nla_total_size(4) /* RTA_PRIORITY */
			 + nla_total_size(4) /* RTA_PREFSRC */
			 + nla_total_size(TCP_CA_NAME_MAX); /* RTAX_CC_ALGO */
	unsigned int nhs = fib_info_num_path(fi);

	/* space for nested metrics */
	payload += nla_total_size((RTAX_MAX * nla_total_size(4)));

	if (fi->nh)
		payload += nla_total_size(4); /* RTA_NH_ID */

	if (nhs) {
		size_t nh_encapsize = 0;
		/* Also handles the special case nhs == 1 */

		/* each nexthop is packed in an attribute */
		size_t nhsize = nla_total_size(sizeof(struct rtnexthop));
		unsigned int i;

		/* may contain flow and gateway attribute */
		nhsize += 2 * nla_total_size(4);

		/* grab encap info */
		for (i = 0; i < fib_info_num_path(fi); i++) {
			struct fib_nh_common *nhc = fib_info_nhc(fi, i);

			if (nhc->nhc_lwtstate) {
				/* RTA_ENCAP_TYPE */
				nh_encapsize += lwtunnel_get_encap_size(
						nhc->nhc_lwtstate);
				/* RTA_ENCAP */
				nh_encapsize +=  nla_total_size(2);
			}
		}

		/* all nexthops are packed in a nested attribute */
		payload += nla_total_size((nhs * nhsize) + nh_encapsize);

	}

	return payload;
}