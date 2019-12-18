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
struct tipc_nl_compat_msg {struct sk_buff* rep; scalar_t__ rep_type; int /*<<< orphan*/  rep_size; scalar_t__ req_type; int /*<<< orphan*/  req; int /*<<< orphan*/  req_size; } ;
struct tipc_nl_compat_cmd_dump {int (* header ) (struct tipc_nl_compat_msg*) ;} ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TLV_CHECK_TYPE (int /*<<< orphan*/ ,scalar_t__) ; 
 int __tipc_nl_compat_dumpit (struct tipc_nl_compat_cmd_dump*,struct tipc_nl_compat_msg*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct tipc_nl_compat_msg*) ; 
 struct sk_buff* tipc_tlv_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_tlv_init (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int tipc_nl_compat_dumpit(struct tipc_nl_compat_cmd_dump *cmd,
				 struct tipc_nl_compat_msg *msg)
{
	int err;
	struct sk_buff *arg;

	if (msg->req_type && (!msg->req_size ||
			      !TLV_CHECK_TYPE(msg->req, msg->req_type)))
		return -EINVAL;

	msg->rep = tipc_tlv_alloc(msg->rep_size);
	if (!msg->rep)
		return -ENOMEM;

	if (msg->rep_type)
		tipc_tlv_init(msg->rep, msg->rep_type);

	if (cmd->header) {
		err = (*cmd->header)(msg);
		if (err) {
			kfree_skb(msg->rep);
			msg->rep = NULL;
			return err;
		}
	}

	arg = nlmsg_new(0, GFP_KERNEL);
	if (!arg) {
		kfree_skb(msg->rep);
		msg->rep = NULL;
		return -ENOMEM;
	}

	err = __tipc_nl_compat_dumpit(cmd, msg, arg);
	if (err) {
		kfree_skb(msg->rep);
		msg->rep = NULL;
	}
	kfree_skb(arg);

	return err;
}