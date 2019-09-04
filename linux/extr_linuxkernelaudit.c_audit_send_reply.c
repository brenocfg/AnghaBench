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
struct task_struct {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct audit_reply {struct sk_buff* skb; int /*<<< orphan*/  portid; int /*<<< orphan*/  net; } ;
struct TYPE_2__ {int /*<<< orphan*/  portid; int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct task_struct*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 struct sk_buff* audit_make_reply (int,int,int,int,void const*,int) ; 
 int /*<<< orphan*/  audit_send_reply_thread ; 
 int /*<<< orphan*/  get_net (struct net*) ; 
 int /*<<< orphan*/  kfree (struct audit_reply*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct audit_reply* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct audit_reply*,char*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void audit_send_reply(struct sk_buff *request_skb, int seq, int type, int done,
			     int multi, const void *payload, int size)
{
	struct net *net = sock_net(NETLINK_CB(request_skb).sk);
	struct sk_buff *skb;
	struct task_struct *tsk;
	struct audit_reply *reply = kmalloc(sizeof(struct audit_reply),
					    GFP_KERNEL);

	if (!reply)
		return;

	skb = audit_make_reply(seq, type, done, multi, payload, size);
	if (!skb)
		goto out;

	reply->net = get_net(net);
	reply->portid = NETLINK_CB(request_skb).portid;
	reply->skb = skb;

	tsk = kthread_run(audit_send_reply_thread, reply, "audit_send_reply");
	if (!IS_ERR(tsk))
		return;
	kfree_skb(skb);
out:
	kfree(reply);
}