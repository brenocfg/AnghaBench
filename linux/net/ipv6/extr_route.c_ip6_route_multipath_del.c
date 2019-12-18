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
struct rtnexthop {scalar_t__ rtnh_ifindex; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct fib6_config {int fc_mp_len; int /*<<< orphan*/  fc_flags; int /*<<< orphan*/  fc_gateway; scalar_t__ fc_ifindex; scalar_t__ fc_mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTA_GATEWAY ; 
 int /*<<< orphan*/  RTF_GATEWAY ; 
 int ip6_route_del (struct fib6_config*,struct netlink_ext_ack*) ; 
 int /*<<< orphan*/  memcpy (struct fib6_config*,struct fib6_config*,int) ; 
 struct nlattr* nla_find (struct nlattr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ *,struct nlattr*,int) ; 
 int rtnh_attrlen (struct rtnexthop*) ; 
 struct nlattr* rtnh_attrs (struct rtnexthop*) ; 
 struct rtnexthop* rtnh_next (struct rtnexthop*,int*) ; 
 scalar_t__ rtnh_ok (struct rtnexthop*,int) ; 

__attribute__((used)) static int ip6_route_multipath_del(struct fib6_config *cfg,
				   struct netlink_ext_ack *extack)
{
	struct fib6_config r_cfg;
	struct rtnexthop *rtnh;
	int remaining;
	int attrlen;
	int err = 1, last_err = 0;

	remaining = cfg->fc_mp_len;
	rtnh = (struct rtnexthop *)cfg->fc_mp;

	/* Parse a Multipath Entry */
	while (rtnh_ok(rtnh, remaining)) {
		memcpy(&r_cfg, cfg, sizeof(*cfg));
		if (rtnh->rtnh_ifindex)
			r_cfg.fc_ifindex = rtnh->rtnh_ifindex;

		attrlen = rtnh_attrlen(rtnh);
		if (attrlen > 0) {
			struct nlattr *nla, *attrs = rtnh_attrs(rtnh);

			nla = nla_find(attrs, attrlen, RTA_GATEWAY);
			if (nla) {
				nla_memcpy(&r_cfg.fc_gateway, nla, 16);
				r_cfg.fc_flags |= RTF_GATEWAY;
			}
		}
		err = ip6_route_del(&r_cfg, extack);
		if (err)
			last_err = err;

		rtnh = rtnh_next(rtnh, &remaining);
	}

	return last_err;
}