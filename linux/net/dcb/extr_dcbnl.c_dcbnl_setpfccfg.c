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
struct nlattr {scalar_t__ nla_type; } ;
struct net_device {TYPE_1__* dcbnl_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* setpfccfg ) (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t DCB_ATTR_PFC_CFG ; 
 int DCB_PFC_UP_ATTR_0 ; 
 int DCB_PFC_UP_ATTR_7 ; 
 int /*<<< orphan*/  DCB_PFC_UP_ATTR_MAX ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dcbnl_pfc_up_nest ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nla_put_u8 (struct sk_buff*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcbnl_setpfccfg(struct net_device *netdev, struct nlmsghdr *nlh,
			   u32 seq, struct nlattr **tb, struct sk_buff *skb)
{
	struct nlattr *data[DCB_PFC_UP_ATTR_MAX + 1];
	int i;
	int ret;
	u8 value;

	if (!tb[DCB_ATTR_PFC_CFG])
		return -EINVAL;

	if (!netdev->dcbnl_ops->setpfccfg)
		return -EOPNOTSUPP;

	ret = nla_parse_nested_deprecated(data, DCB_PFC_UP_ATTR_MAX,
					  tb[DCB_ATTR_PFC_CFG],
					  dcbnl_pfc_up_nest, NULL);
	if (ret)
		return ret;

	for (i = DCB_PFC_UP_ATTR_0; i <= DCB_PFC_UP_ATTR_7; i++) {
		if (data[i] == NULL)
			continue;
		value = nla_get_u8(data[i]);
		netdev->dcbnl_ops->setpfccfg(netdev,
			data[i]->nla_type - DCB_PFC_UP_ATTR_0, value);
	}

	return nla_put_u8(skb, DCB_ATTR_PFC_CFG, 0);
}