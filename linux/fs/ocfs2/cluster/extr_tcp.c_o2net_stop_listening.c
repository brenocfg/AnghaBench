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
struct socket {TYPE_1__* sk; } ;
struct o2nm_node {int /*<<< orphan*/  nd_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/ * sk_user_data; int /*<<< orphan*/ * sk_data_ready; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ML_KTHREAD ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  o2net_disconnect_node (struct o2nm_node*) ; 
 struct socket* o2net_listen_sock ; 
 int /*<<< orphan*/  o2net_nodes ; 
 int /*<<< orphan*/ * o2net_wq ; 
 struct o2nm_node* o2nm_get_node_by_num (size_t) ; 
 int /*<<< orphan*/  o2nm_node_put (struct o2nm_node*) ; 
 int /*<<< orphan*/  o2quo_conn_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void o2net_stop_listening(struct o2nm_node *node)
{
	struct socket *sock = o2net_listen_sock;
	size_t i;

	BUG_ON(o2net_wq == NULL);
	BUG_ON(o2net_listen_sock == NULL);

	/* stop the listening socket from generating work */
	write_lock_bh(&sock->sk->sk_callback_lock);
	sock->sk->sk_data_ready = sock->sk->sk_user_data;
	sock->sk->sk_user_data = NULL;
	write_unlock_bh(&sock->sk->sk_callback_lock);

	for (i = 0; i < ARRAY_SIZE(o2net_nodes); i++) {
		struct o2nm_node *node = o2nm_get_node_by_num(i);
		if (node) {
			o2net_disconnect_node(node);
			o2nm_node_put(node);
		}
	}

	/* finish all work and tear down the work queue */
	mlog(ML_KTHREAD, "waiting for o2net thread to exit....\n");
	destroy_workqueue(o2net_wq);
	o2net_wq = NULL;

	sock_release(o2net_listen_sock);
	o2net_listen_sock = NULL;

	o2quo_conn_err(node->nd_num);
}