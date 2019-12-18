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
struct TYPE_2__ {int (* getnumtcs ) (struct net_device*,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 size_t DCB_ATTR_NUMTCS ; 
 size_t DCB_NUMTCS_ATTR_ALL ; 
 int DCB_NUMTCS_ATTR_MAX ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dcbnl_numtcs_nest ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,size_t) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nla_put_u8 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct net_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dcbnl_getnumtcs(struct net_device *netdev, struct nlmsghdr *nlh,
			   u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	struct nlattr *data[DCB_NUMTCS_ATTR_MAX + 1], *nest;
	u8 value;
	int ret;
	int i;
	int getall = 0;

	if (!tb[DCB_ATTR_NUMTCS])
		return -EINVAL;

	if (!netdev->dcbnl_ops->getnumtcs)
		return -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(data, DCB_NUMTCS_ATTR_MAX,
					  tb[DCB_ATTR_NUMTCS],
					  dcbnl_numtcs_nest, NULL);
	if (ret)
		return ret;

	nest = nla_nest_start_noflag(skb, DCB_ATTR_NUMTCS);
	if (!nest)
		return -EMSGSIZE;

	if (data[DCB_NUMTCS_ATTR_ALL])
		getall = 1;

	for (i = DCB_NUMTCS_ATTR_ALL+1; i <= DCB_NUMTCS_ATTR_MAX; i++) {
		if (!getall && !data[i])
			continue;

		ret = netdev->dcbnl_ops->getnumtcs(netdev, i, &value);
		if (!ret) {
			ret = nla_put_u8(skb, i, value);
			if (ret) {
				nla_nest_cancel(skb, nest);
				return ret;
			}
		} else
			return -EINVAL;
	}
	nla_nest_end(skb, nest);

	return 0;
}