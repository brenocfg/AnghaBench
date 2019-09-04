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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct genl_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  family ; 
 struct sk_buff* genlmsg_new (size_t,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put_reply (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int /*<<< orphan*/  taskstats_seqnum ; 
 int this_cpu_inc_return (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prepare_reply(struct genl_info *info, u8 cmd, struct sk_buff **skbp,
				size_t size)
{
	struct sk_buff *skb;
	void *reply;

	/*
	 * If new attributes are added, please revisit this allocation
	 */
	skb = genlmsg_new(size, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	if (!info) {
		int seq = this_cpu_inc_return(taskstats_seqnum) - 1;

		reply = genlmsg_put(skb, 0, seq, &family, 0, cmd);
	} else
		reply = genlmsg_put_reply(skb, info, &family, 0, cmd);
	if (reply == NULL) {
		nlmsg_free(skb);
		return -EINVAL;
	}

	*skbp = skb;
	return 0;
}