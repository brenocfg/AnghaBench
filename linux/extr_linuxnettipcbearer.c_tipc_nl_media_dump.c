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
struct tipc_nl_msg {int /*<<< orphan*/  seq; int /*<<< orphan*/  portid; struct sk_buff* skb; } ;
struct sk_buff {int len; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int MAX_MEDIA ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int __tipc_nl_add_media (struct tipc_nl_msg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** media_info_array ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

int tipc_nl_media_dump(struct sk_buff *skb, struct netlink_callback *cb)
{
	int err;
	int i = cb->args[0];
	struct tipc_nl_msg msg;

	if (i == MAX_MEDIA)
		return 0;

	msg.skb = skb;
	msg.portid = NETLINK_CB(cb->skb).portid;
	msg.seq = cb->nlh->nlmsg_seq;

	rtnl_lock();
	for (; media_info_array[i] != NULL; i++) {
		err = __tipc_nl_add_media(&msg, media_info_array[i],
					  NLM_F_MULTI);
		if (err)
			break;
	}
	rtnl_unlock();

	cb->args[0] = i;
	return skb->len;
}