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
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct audit_netlink_list {int /*<<< orphan*/  q; int /*<<< orphan*/  portid; int /*<<< orphan*/  net; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 TYPE_1__ NETLINK_CB (struct sk_buff*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  audit_filter_mutex ; 
 int /*<<< orphan*/  audit_list_rules (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_send_list ; 
 int /*<<< orphan*/  get_net (struct net*) ; 
 int /*<<< orphan*/  kfree (struct audit_netlink_list*) ; 
 struct audit_netlink_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct audit_netlink_list*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

int audit_list_rules_send(struct sk_buff *request_skb, int seq)
{
	u32 portid = NETLINK_CB(request_skb).portid;
	struct net *net = sock_net(NETLINK_CB(request_skb).sk);
	struct task_struct *tsk;
	struct audit_netlink_list *dest;
	int err = 0;

	/* We can't just spew out the rules here because we might fill
	 * the available socket buffer space and deadlock waiting for
	 * auditctl to read from it... which isn't ever going to
	 * happen if we're actually running in the context of auditctl
	 * trying to _send_ the stuff */

	dest = kmalloc(sizeof(struct audit_netlink_list), GFP_KERNEL);
	if (!dest)
		return -ENOMEM;
	dest->net = get_net(net);
	dest->portid = portid;
	skb_queue_head_init(&dest->q);

	mutex_lock(&audit_filter_mutex);
	audit_list_rules(seq, &dest->q);
	mutex_unlock(&audit_filter_mutex);

	tsk = kthread_run(audit_send_list, dest, "audit_send_list");
	if (IS_ERR(tsk)) {
		skb_queue_purge(&dest->q);
		kfree(dest);
		err = PTR_ERR(tsk);
	}

	return err;
}