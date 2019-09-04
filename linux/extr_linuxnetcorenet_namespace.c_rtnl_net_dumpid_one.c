#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtnl_net_dump_cb {scalar_t__ idx; scalar_t__ s_idx; int /*<<< orphan*/  net; TYPE_2__* cb; int /*<<< orphan*/  skb; } ;
struct TYPE_6__ {int /*<<< orphan*/  portid; } ;
struct TYPE_5__ {TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 TYPE_3__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  RTM_NEWNSID ; 
 int rtnl_net_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtnl_net_dumpid_one(int id, void *peer, void *data)
{
	struct rtnl_net_dump_cb *net_cb = (struct rtnl_net_dump_cb *)data;
	int ret;

	if (net_cb->idx < net_cb->s_idx)
		goto cont;

	ret = rtnl_net_fill(net_cb->skb, NETLINK_CB(net_cb->cb->skb).portid,
			    net_cb->cb->nlh->nlmsg_seq, NLM_F_MULTI,
			    RTM_NEWNSID, net_cb->net, id);
	if (ret < 0)
		return ret;

cont:
	net_cb->idx++;
	return 0;
}