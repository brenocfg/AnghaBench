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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int flags; } ;
struct net {int dummy; } ;
struct flowi4 {scalar_t__ flowi4_scope; int /*<<< orphan*/  flowi4_iif; int /*<<< orphan*/  flowi4_oif; int /*<<< orphan*/  daddr; } ;
struct fib_table {int dummy; } ;
struct fib_result {unsigned int type; scalar_t__ scope; } ;
struct fib_nh {int fib_nh_flags; struct net_device* fib_nh_dev; int /*<<< orphan*/  fib_nh_oif; scalar_t__ fib_nh_scope; int /*<<< orphan*/  fib_nh_gw4; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 int ENODEV ; 
 int FIB_LOOKUP_IGNORE_LINKSTATE ; 
 int FIB_LOOKUP_NOREF ; 
 struct net_device* FIB_RES_DEV (struct fib_result) ; 
 int /*<<< orphan*/  FIB_RES_OIF (struct fib_result) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  LOOPBACK_IFINDEX ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int RTNH_F_LINKDOWN ; 
 int RTNH_F_ONLINK ; 
 unsigned int RTN_LOCAL ; 
 unsigned int RTN_UNICAST ; 
 scalar_t__ RT_SCOPE_LINK ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct fib_table* fib_get_table (struct net*,scalar_t__) ; 
 int fib_lookup (struct net*,struct flowi4*,struct fib_result*,int) ; 
 int fib_table_lookup (struct fib_table*,struct flowi4*,struct fib_result*,int) ; 
 unsigned int inet_addr_type_dev_table (struct net*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int fib_check_nh_v4_gw(struct net *net, struct fib_nh *nh, u32 table,
			      u8 scope, struct netlink_ext_ack *extack)
{
	struct net_device *dev;
	struct fib_result res;
	int err = 0;

	if (nh->fib_nh_flags & RTNH_F_ONLINK) {
		unsigned int addr_type;

		if (scope >= RT_SCOPE_LINK) {
			NL_SET_ERR_MSG(extack, "Nexthop has invalid scope");
			return -EINVAL;
		}
		dev = __dev_get_by_index(net, nh->fib_nh_oif);
		if (!dev) {
			NL_SET_ERR_MSG(extack, "Nexthop device required for onlink");
			return -ENODEV;
		}
		if (!(dev->flags & IFF_UP)) {
			NL_SET_ERR_MSG(extack, "Nexthop device is not up");
			return -ENETDOWN;
		}
		addr_type = inet_addr_type_dev_table(net, dev, nh->fib_nh_gw4);
		if (addr_type != RTN_UNICAST) {
			NL_SET_ERR_MSG(extack, "Nexthop has invalid gateway");
			return -EINVAL;
		}
		if (!netif_carrier_ok(dev))
			nh->fib_nh_flags |= RTNH_F_LINKDOWN;
		nh->fib_nh_dev = dev;
		dev_hold(dev);
		nh->fib_nh_scope = RT_SCOPE_LINK;
		return 0;
	}
	rcu_read_lock();
	{
		struct fib_table *tbl = NULL;
		struct flowi4 fl4 = {
			.daddr = nh->fib_nh_gw4,
			.flowi4_scope = scope + 1,
			.flowi4_oif = nh->fib_nh_oif,
			.flowi4_iif = LOOPBACK_IFINDEX,
		};

		/* It is not necessary, but requires a bit of thinking */
		if (fl4.flowi4_scope < RT_SCOPE_LINK)
			fl4.flowi4_scope = RT_SCOPE_LINK;

		if (table)
			tbl = fib_get_table(net, table);

		if (tbl)
			err = fib_table_lookup(tbl, &fl4, &res,
					       FIB_LOOKUP_IGNORE_LINKSTATE |
					       FIB_LOOKUP_NOREF);

		/* on error or if no table given do full lookup. This
		 * is needed for example when nexthops are in the local
		 * table rather than the given table
		 */
		if (!tbl || err) {
			err = fib_lookup(net, &fl4, &res,
					 FIB_LOOKUP_IGNORE_LINKSTATE);
		}

		if (err) {
			NL_SET_ERR_MSG(extack, "Nexthop has invalid gateway");
			goto out;
		}
	}

	err = -EINVAL;
	if (res.type != RTN_UNICAST && res.type != RTN_LOCAL) {
		NL_SET_ERR_MSG(extack, "Nexthop has invalid gateway");
		goto out;
	}
	nh->fib_nh_scope = res.scope;
	nh->fib_nh_oif = FIB_RES_OIF(res);
	nh->fib_nh_dev = dev = FIB_RES_DEV(res);
	if (!dev) {
		NL_SET_ERR_MSG(extack,
			       "No egress device for nexthop gateway");
		goto out;
	}
	dev_hold(dev);
	if (!netif_carrier_ok(dev))
		nh->fib_nh_flags |= RTNH_F_LINKDOWN;
	err = (dev->flags & IFF_UP) ? 0 : -ENETDOWN;
out:
	rcu_read_unlock();
	return err;
}