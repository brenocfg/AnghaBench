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
struct o2net_sock_container {int /*<<< orphan*/  sc_idle_timeout; TYPE_1__* sc_node; } ;
struct o2net_node {int /*<<< orphan*/  nn_timeout; int /*<<< orphan*/  nn_still_up; } ;
struct TYPE_2__ {int /*<<< orphan*/  nd_num; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 struct o2net_node* o2net_nn_from_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  o2net_num_from_nn (struct o2net_node*) ; 
 int /*<<< orphan*/  o2net_sc_reset_idle_timer (struct o2net_sock_container*) ; 
 int /*<<< orphan*/  o2quo_conn_up (int /*<<< orphan*/ ) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2net_sc_postpone_idle(struct o2net_sock_container *sc)
{
	struct o2net_node *nn = o2net_nn_from_num(sc->sc_node->nd_num);

	/* clear fence decision since the connection recover from timeout*/
	if (atomic_read(&nn->nn_timeout)) {
		o2quo_conn_up(o2net_num_from_nn(nn));
		cancel_delayed_work(&nn->nn_still_up);
		atomic_set(&nn->nn_timeout, 0);
	}

	/* Only push out an existing timer */
	if (timer_pending(&sc->sc_idle_timeout))
		o2net_sc_reset_idle_timer(sc);
}