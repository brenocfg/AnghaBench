#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct netlink_callback {TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct ipvs_sync_daemon_cfg {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  IPVS_CMD_NEW_DAEMON ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_vs_genl_family ; 
 scalar_t__ ip_vs_genl_fill_daemon (struct sk_buff*,int /*<<< orphan*/ ,struct ipvs_sync_daemon_cfg*) ; 

__attribute__((used)) static int ip_vs_genl_dump_daemon(struct sk_buff *skb, __u32 state,
				  struct ipvs_sync_daemon_cfg *c,
				  struct netlink_callback *cb)
{
	void *hdr;
	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &ip_vs_genl_family, NLM_F_MULTI,
			  IPVS_CMD_NEW_DAEMON);
	if (!hdr)
		return -EMSGSIZE;

	if (ip_vs_genl_fill_daemon(skb, state, c))
		goto nla_put_failure;

	genlmsg_end(skb, hdr);
	return 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	return -EMSGSIZE;
}