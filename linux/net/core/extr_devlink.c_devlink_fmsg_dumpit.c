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
struct sk_buff {int len; } ;
struct netlink_callback {int* args; TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct devlink_fmsg {int dummy; } ;
typedef  enum devlink_command { ____Placeholder_devlink_command } devlink_command ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int NLM_F_ACK ; 
 int NLM_F_MULTI ; 
 int devlink_fmsg_prepare_skb (struct devlink_fmsg*,struct sk_buff*,int*) ; 
 int /*<<< orphan*/  devlink_nl_family ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int devlink_fmsg_dumpit(struct devlink_fmsg *fmsg, struct sk_buff *skb,
			       struct netlink_callback *cb,
			       enum devlink_command cmd)
{
	int index = cb->args[0];
	int tmp_index = index;
	void *hdr;
	int err;

	hdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &devlink_nl_family, NLM_F_ACK | NLM_F_MULTI, cmd);
	if (!hdr) {
		err = -EMSGSIZE;
		goto nla_put_failure;
	}

	err = devlink_fmsg_prepare_skb(fmsg, skb, &index);
	if ((err && err != -EMSGSIZE) || tmp_index == index)
		goto nla_put_failure;

	cb->args[0] = index;
	genlmsg_end(skb, hdr);
	return skb->len;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	return err;
}