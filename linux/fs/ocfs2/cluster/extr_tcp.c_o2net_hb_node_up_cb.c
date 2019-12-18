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
struct o2nm_node {int dummy; } ;
struct o2net_node {int /*<<< orphan*/  nn_lock; scalar_t__ nn_persistent_error; int /*<<< orphan*/  nn_timeout; scalar_t__ nn_last_connect_attempt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct o2net_node* o2net_nn_from_num (int) ; 
 int /*<<< orphan*/  o2net_reconnect_delay () ; 
 int /*<<< orphan*/  o2net_set_nn_state (struct o2net_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int o2nm_this_node () ; 
 int /*<<< orphan*/  o2quo_hb_up (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2net_hb_node_up_cb(struct o2nm_node *node, int node_num,
				void *data)
{
	struct o2net_node *nn = o2net_nn_from_num(node_num);

	o2quo_hb_up(node_num);

	BUG_ON(!node);

	/* ensure an immediate connect attempt */
	nn->nn_last_connect_attempt = jiffies -
		(msecs_to_jiffies(o2net_reconnect_delay()) + 1);

	if (node_num != o2nm_this_node()) {
		/* believe it or not, accept and node heartbeating testing
		 * can succeed for this node before we got here.. so
		 * only use set_nn_state to clear the persistent error
		 * if that hasn't already happened */
		spin_lock(&nn->nn_lock);
		atomic_set(&nn->nn_timeout, 0);
		if (nn->nn_persistent_error)
			o2net_set_nn_state(nn, NULL, 0, 0);
		spin_unlock(&nn->nn_lock);
	}
}