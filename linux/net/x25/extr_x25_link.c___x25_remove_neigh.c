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
struct TYPE_2__ {scalar_t__ next; } ;
struct x25_neigh {TYPE_1__ node; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x25_neigh_put (struct x25_neigh*) ; 
 int /*<<< orphan*/  x25_stop_t20timer (struct x25_neigh*) ; 

__attribute__((used)) static void __x25_remove_neigh(struct x25_neigh *nb)
{
	skb_queue_purge(&nb->queue);
	x25_stop_t20timer(nb);

	if (nb->node.next) {
		list_del(&nb->node);
		x25_neigh_put(nb);
	}
}