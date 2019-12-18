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
struct TYPE_2__ {int nsid; int /*<<< orphan*/  ref_nsid; scalar_t__ add_ref; } ;
struct rtnl_net_dump_cb {scalar_t__ idx; scalar_t__ s_idx; TYPE_1__ fillargs; int /*<<< orphan*/  skb; int /*<<< orphan*/  ref_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  __peernet2id (int /*<<< orphan*/ ,void*) ; 
 int rtnl_net_fill (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int rtnl_net_dumpid_one(int id, void *peer, void *data)
{
	struct rtnl_net_dump_cb *net_cb = (struct rtnl_net_dump_cb *)data;
	int ret;

	if (net_cb->idx < net_cb->s_idx)
		goto cont;

	net_cb->fillargs.nsid = id;
	if (net_cb->fillargs.add_ref)
		net_cb->fillargs.ref_nsid = __peernet2id(net_cb->ref_net, peer);
	ret = rtnl_net_fill(net_cb->skb, &net_cb->fillargs);
	if (ret < 0)
		return ret;

cont:
	net_cb->idx++;
	return 0;
}