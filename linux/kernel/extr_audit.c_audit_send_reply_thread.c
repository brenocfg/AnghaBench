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
struct sock {int dummy; } ;
struct audit_reply {int /*<<< orphan*/  net; int /*<<< orphan*/  portid; int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_ctl_lock () ; 
 int /*<<< orphan*/  audit_ctl_unlock () ; 
 struct sock* audit_get_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct audit_reply*) ; 
 int /*<<< orphan*/  netlink_unicast (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audit_send_reply_thread(void *arg)
{
	struct audit_reply *reply = (struct audit_reply *)arg;
	struct sock *sk = audit_get_sk(reply->net);

	audit_ctl_lock();
	audit_ctl_unlock();

	/* Ignore failure. It'll only happen if the sender goes away,
	   because our timeout is set to infinite. */
	netlink_unicast(sk, reply->skb, reply->portid, 0);
	put_net(reply->net);
	kfree(reply);
	return 0;
}