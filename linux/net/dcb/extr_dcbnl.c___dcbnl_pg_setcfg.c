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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {TYPE_1__* dcbnl_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* setpgbwgcfgtx ) (struct net_device*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setpgbwgcfgrx ) (struct net_device*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setpgtccfgtx ) (struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* setpgtccfgrx ) (struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t DCB_ATTR_PG_CFG ; 
 int /*<<< orphan*/  DCB_ATTR_VALUE_UNDEFINED ; 
 int DCB_PG_ATTR_BW_ID_0 ; 
 int DCB_PG_ATTR_BW_ID_7 ; 
 int /*<<< orphan*/  DCB_PG_ATTR_MAX ; 
 int DCB_PG_ATTR_TC_0 ; 
 int DCB_PG_ATTR_TC_7 ; 
 size_t DCB_TC_ATTR_PARAM_BW_PCT ; 
 int /*<<< orphan*/  DCB_TC_ATTR_PARAM_MAX ; 
 size_t DCB_TC_ATTR_PARAM_PGID ; 
 size_t DCB_TC_ATTR_PARAM_STRICT_PRIO ; 
 size_t DCB_TC_ATTR_PARAM_UP_MAPPING ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dcbnl_pg_nest ; 
 int /*<<< orphan*/  dcbnl_tc_param_nest ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nla_put_u8 (struct sk_buff*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __dcbnl_pg_setcfg(struct net_device *netdev, struct nlmsghdr *nlh,
			     u32 seq, struct nlattr **tb, struct sk_buff *skb,
			     int dir)
{
	struct nlattr *pg_tb[DCB_PG_ATTR_MAX + 1];
	struct nlattr *param_tb[DCB_TC_ATTR_PARAM_MAX + 1];
	int ret;
	int i;
	u8 pgid;
	u8 up_map;
	u8 prio;
	u8 tc_pct;

	if (!tb[DCB_ATTR_PG_CFG])
		return -EINVAL;

	if (!netdev->dcbnl_ops->setpgtccfgtx ||
	    !netdev->dcbnl_ops->setpgtccfgrx ||
	    !netdev->dcbnl_ops->setpgbwgcfgtx ||
	    !netdev->dcbnl_ops->setpgbwgcfgrx)
		return -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(pg_tb, DCB_PG_ATTR_MAX,
					  tb[DCB_ATTR_PG_CFG], dcbnl_pg_nest,
					  NULL);
	if (ret)
		return ret;

	for (i = DCB_PG_ATTR_TC_0; i <= DCB_PG_ATTR_TC_7; i++) {
		if (!pg_tb[i])
			continue;

		ret = nla_parse_nested_deprecated(param_tb,
						  DCB_TC_ATTR_PARAM_MAX,
						  pg_tb[i],
						  dcbnl_tc_param_nest, NULL);
		if (ret)
			return ret;

		pgid = DCB_ATTR_VALUE_UNDEFINED;
		prio = DCB_ATTR_VALUE_UNDEFINED;
		tc_pct = DCB_ATTR_VALUE_UNDEFINED;
		up_map = DCB_ATTR_VALUE_UNDEFINED;

		if (param_tb[DCB_TC_ATTR_PARAM_STRICT_PRIO])
			prio =
			    nla_get_u8(param_tb[DCB_TC_ATTR_PARAM_STRICT_PRIO]);

		if (param_tb[DCB_TC_ATTR_PARAM_PGID])
			pgid = nla_get_u8(param_tb[DCB_TC_ATTR_PARAM_PGID]);

		if (param_tb[DCB_TC_ATTR_PARAM_BW_PCT])
			tc_pct = nla_get_u8(param_tb[DCB_TC_ATTR_PARAM_BW_PCT]);

		if (param_tb[DCB_TC_ATTR_PARAM_UP_MAPPING])
			up_map =
			     nla_get_u8(param_tb[DCB_TC_ATTR_PARAM_UP_MAPPING]);

		/* dir: Tx = 0, Rx = 1 */
		if (dir) {
			/* Rx */
			netdev->dcbnl_ops->setpgtccfgrx(netdev,
				i - DCB_PG_ATTR_TC_0,
				prio, pgid, tc_pct, up_map);
		} else {
			/* Tx */
			netdev->dcbnl_ops->setpgtccfgtx(netdev,
				i - DCB_PG_ATTR_TC_0,
				prio, pgid, tc_pct, up_map);
		}
	}

	for (i = DCB_PG_ATTR_BW_ID_0; i <= DCB_PG_ATTR_BW_ID_7; i++) {
		if (!pg_tb[i])
			continue;

		tc_pct = nla_get_u8(pg_tb[i]);

		/* dir: Tx = 0, Rx = 1 */
		if (dir) {
			/* Rx */
			netdev->dcbnl_ops->setpgbwgcfgrx(netdev,
					 i - DCB_PG_ATTR_BW_ID_0, tc_pct);
		} else {
			/* Tx */
			netdev->dcbnl_ops->setpgbwgcfgtx(netdev,
					 i - DCB_PG_ATTR_BW_ID_0, tc_pct);
		}
	}

	return nla_put_u8(skb, DCB_ATTR_PG_CFG, 0);
}