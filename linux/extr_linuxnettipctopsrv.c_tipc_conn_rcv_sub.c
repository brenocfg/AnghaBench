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
struct tipc_topsrv {int /*<<< orphan*/  net; } ;
struct tipc_subscription {int /*<<< orphan*/  sub_list; } ;
struct tipc_subscr {int /*<<< orphan*/  filter; } ;
struct tipc_net {int /*<<< orphan*/  subscription_count; } ;
struct tipc_conn {int /*<<< orphan*/  sub_lock; int /*<<< orphan*/  sub_list; int /*<<< orphan*/  conid; } ;

/* Variables and functions */
 scalar_t__ TIPC_MAX_SUBSCR ; 
 int TIPC_SUB_CANCEL ; 
 int /*<<< orphan*/  __constant_ntohl (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filter ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_conn_delete_sub (struct tipc_conn*,struct tipc_subscr*) ; 
 struct tipc_net* tipc_net (int /*<<< orphan*/ ) ; 
 int tipc_sub_read (struct tipc_subscr*,int /*<<< orphan*/ ) ; 
 struct tipc_subscription* tipc_sub_subscribe (int /*<<< orphan*/ ,struct tipc_subscr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tipc_conn_rcv_sub(struct tipc_topsrv *srv,
			     struct tipc_conn *con,
			     struct tipc_subscr *s)
{
	struct tipc_net *tn = tipc_net(srv->net);
	struct tipc_subscription *sub;

	if (tipc_sub_read(s, filter) & TIPC_SUB_CANCEL) {
		s->filter &= __constant_ntohl(~TIPC_SUB_CANCEL);
		tipc_conn_delete_sub(con, s);
		return 0;
	}
	if (atomic_read(&tn->subscription_count) >= TIPC_MAX_SUBSCR) {
		pr_warn("Subscription rejected, max (%u)\n", TIPC_MAX_SUBSCR);
		return -1;
	}
	sub = tipc_sub_subscribe(srv->net, s, con->conid);
	if (!sub)
		return -1;
	atomic_inc(&tn->subscription_count);
	spin_lock_bh(&con->sub_lock);
	list_add(&sub->sub_list, &con->sub_list);
	spin_unlock_bh(&con->sub_lock);
	return 0;
}