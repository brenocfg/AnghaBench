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
struct l2tp_tunnel {int /*<<< orphan*/  del_work; int /*<<< orphan*/  dead; } ;

/* Variables and functions */
 int /*<<< orphan*/  l2tp_tunnel_inc_refcount (struct l2tp_tunnel*) ; 
 int /*<<< orphan*/  l2tp_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void l2tp_tunnel_delete(struct l2tp_tunnel *tunnel)
{
	if (!test_and_set_bit(0, &tunnel->dead)) {
		l2tp_tunnel_inc_refcount(tunnel);
		queue_work(l2tp_wq, &tunnel->del_work);
	}
}