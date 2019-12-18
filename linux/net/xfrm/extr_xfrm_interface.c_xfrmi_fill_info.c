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
struct xfrm_if_parms {int /*<<< orphan*/  if_id; int /*<<< orphan*/  link; } ;
struct xfrm_if {struct xfrm_if_parms p; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IFLA_XFRM_IF_ID ; 
 int /*<<< orphan*/  IFLA_XFRM_LINK ; 
 struct xfrm_if* netdev_priv (struct net_device const*) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrmi_fill_info(struct sk_buff *skb, const struct net_device *dev)
{
	struct xfrm_if *xi = netdev_priv(dev);
	struct xfrm_if_parms *parm = &xi->p;

	if (nla_put_u32(skb, IFLA_XFRM_LINK, parm->link) ||
	    nla_put_u32(skb, IFLA_XFRM_IF_ID, parm->if_id))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -EMSGSIZE;
}