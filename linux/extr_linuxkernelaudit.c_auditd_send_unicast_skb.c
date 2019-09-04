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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct auditd_connection {int /*<<< orphan*/  portid; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int ECONNREFUSED ; 
 struct sock* audit_get_sk (struct net*) ; 
 int /*<<< orphan*/  auditd_conn ; 
 int /*<<< orphan*/  auditd_reset (struct auditd_connection*) ; 
 struct net* get_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int netlink_unicast (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_net (struct net*) ; 
 struct auditd_connection* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int auditd_send_unicast_skb(struct sk_buff *skb)
{
	int rc;
	u32 portid;
	struct net *net;
	struct sock *sk;
	struct auditd_connection *ac;

	/* NOTE: we can't call netlink_unicast while in the RCU section so
	 *       take a reference to the network namespace and grab local
	 *       copies of the namespace, the sock, and the portid; the
	 *       namespace and sock aren't going to go away while we hold a
	 *       reference and if the portid does become invalid after the RCU
	 *       section netlink_unicast() should safely return an error */

	rcu_read_lock();
	ac = rcu_dereference(auditd_conn);
	if (!ac) {
		rcu_read_unlock();
		kfree_skb(skb);
		rc = -ECONNREFUSED;
		goto err;
	}
	net = get_net(ac->net);
	sk = audit_get_sk(net);
	portid = ac->portid;
	rcu_read_unlock();

	rc = netlink_unicast(sk, skb, portid, 0);
	put_net(net);
	if (rc < 0)
		goto err;

	return rc;

err:
	if (ac && rc == -ECONNREFUSED)
		auditd_reset(ac);
	return rc;
}