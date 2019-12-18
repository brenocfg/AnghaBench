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
struct tipc_node {int link_cnt; int keepalive_intv; int /*<<< orphan*/  timer; int /*<<< orphan*/  net; struct tipc_link_entry* links; } ;
struct tipc_link_entry {int /*<<< orphan*/  maddr; int /*<<< orphan*/  lock; int /*<<< orphan*/  link; } ;
struct timer_list {int dummy; } ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int MAX_BEARERS ; 
 int TIPC_LINK_DOWN_EVT ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 struct tipc_node* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 struct tipc_node* n ; 
 int /*<<< orphan*/  node_is_up (struct tipc_node*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  tipc_bearer_xmit (int /*<<< orphan*/ ,int,struct sk_buff_head*,int /*<<< orphan*/ *) ; 
 int tipc_link_timeout (int /*<<< orphan*/ ,struct sk_buff_head*) ; 
 int /*<<< orphan*/  tipc_node_calculate_timer (struct tipc_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ tipc_node_cleanup (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_link_down (struct tipc_node*,int,int) ; 
 int /*<<< orphan*/  tipc_node_put (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_read_lock (struct tipc_node*) ; 
 int /*<<< orphan*/  tipc_node_read_unlock (struct tipc_node*) ; 
 int /*<<< orphan*/  trace_tipc_node_timeout (struct tipc_node*,int,char*) ; 

__attribute__((used)) static void tipc_node_timeout(struct timer_list *t)
{
	struct tipc_node *n = from_timer(n, t, timer);
	struct tipc_link_entry *le;
	struct sk_buff_head xmitq;
	int remains = n->link_cnt;
	int bearer_id;
	int rc = 0;

	trace_tipc_node_timeout(n, false, " ");
	if (!node_is_up(n) && tipc_node_cleanup(n)) {
		/*Removing the reference of Timer*/
		tipc_node_put(n);
		return;
	}

	__skb_queue_head_init(&xmitq);

	/* Initial node interval to value larger (10 seconds), then it will be
	 * recalculated with link lowest tolerance
	 */
	tipc_node_read_lock(n);
	n->keepalive_intv = 10000;
	tipc_node_read_unlock(n);
	for (bearer_id = 0; remains && (bearer_id < MAX_BEARERS); bearer_id++) {
		tipc_node_read_lock(n);
		le = &n->links[bearer_id];
		if (le->link) {
			spin_lock_bh(&le->lock);
			/* Link tolerance may change asynchronously: */
			tipc_node_calculate_timer(n, le->link);
			rc = tipc_link_timeout(le->link, &xmitq);
			spin_unlock_bh(&le->lock);
			remains--;
		}
		tipc_node_read_unlock(n);
		tipc_bearer_xmit(n->net, bearer_id, &xmitq, &le->maddr);
		if (rc & TIPC_LINK_DOWN_EVT)
			tipc_node_link_down(n, bearer_id, false);
	}
	mod_timer(&n->timer, jiffies + msecs_to_jiffies(n->keepalive_intv));
}