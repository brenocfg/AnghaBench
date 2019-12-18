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
struct nlattr {int dummy; } ;
struct nexthop_grp {int weight; scalar_t__ id; scalar_t__ resvd2; scalar_t__ resvd1; } ;
struct nexthop {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NHA_GROUP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 unsigned int __NHA_MAX ; 
 struct nexthop* nexthop_find_by_id (struct net*,scalar_t__) ; 
 struct nexthop_grp* nla_data (struct nlattr*) ; 
 unsigned int nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  valid_group_nh (struct nexthop*,unsigned int,struct netlink_ext_ack*) ; 

__attribute__((used)) static int nh_check_attr_group(struct net *net, struct nlattr *tb[],
			       struct netlink_ext_ack *extack)
{
	unsigned int len = nla_len(tb[NHA_GROUP]);
	struct nexthop_grp *nhg;
	unsigned int i, j;

	if (len & (sizeof(struct nexthop_grp) - 1)) {
		NL_SET_ERR_MSG(extack,
			       "Invalid length for nexthop group attribute");
		return -EINVAL;
	}

	/* convert len to number of nexthop ids */
	len /= sizeof(*nhg);

	nhg = nla_data(tb[NHA_GROUP]);
	for (i = 0; i < len; ++i) {
		if (nhg[i].resvd1 || nhg[i].resvd2) {
			NL_SET_ERR_MSG(extack, "Reserved fields in nexthop_grp must be 0");
			return -EINVAL;
		}
		if (nhg[i].weight > 254) {
			NL_SET_ERR_MSG(extack, "Invalid value for weight");
			return -EINVAL;
		}
		for (j = i + 1; j < len; ++j) {
			if (nhg[i].id == nhg[j].id) {
				NL_SET_ERR_MSG(extack, "Nexthop id can not be used twice in a group");
				return -EINVAL;
			}
		}
	}

	nhg = nla_data(tb[NHA_GROUP]);
	for (i = 0; i < len; ++i) {
		struct nexthop *nh;

		nh = nexthop_find_by_id(net, nhg[i].id);
		if (!nh) {
			NL_SET_ERR_MSG(extack, "Invalid nexthop id");
			return -EINVAL;
		}
		if (!valid_group_nh(nh, len, extack))
			return -EINVAL;
	}
	for (i = NHA_GROUP + 1; i < __NHA_MAX; ++i) {
		if (!tb[i])
			continue;

		NL_SET_ERR_MSG(extack,
			       "No other attributes can be set in nexthop groups");
		return -EINVAL;
	}

	return 0;
}