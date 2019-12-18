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
struct x25_neigh {int global_facil_mask; int /*<<< orphan*/  node; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  t20; scalar_t__ extended; int /*<<< orphan*/  state; struct net_device* dev; int /*<<< orphan*/  t20timer; int /*<<< orphan*/  queue; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  X25_LINK_STATE_0 ; 
 int X25_MASK_PACKET_SIZE ; 
 int X25_MASK_REVERSE ; 
 int X25_MASK_THROUGHPUT ; 
 int X25_MASK_WINDOW_SIZE ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct x25_neigh* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_x25_restart_request_timeout ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x25_neigh_list ; 
 int /*<<< orphan*/  x25_neigh_list_lock ; 
 int /*<<< orphan*/  x25_t20timer_expiry ; 

void x25_link_device_up(struct net_device *dev)
{
	struct x25_neigh *nb = kmalloc(sizeof(*nb), GFP_ATOMIC);

	if (!nb)
		return;

	skb_queue_head_init(&nb->queue);
	timer_setup(&nb->t20timer, x25_t20timer_expiry, 0);

	dev_hold(dev);
	nb->dev      = dev;
	nb->state    = X25_LINK_STATE_0;
	nb->extended = 0;
	/*
	 * Enables negotiation
	 */
	nb->global_facil_mask = X25_MASK_REVERSE |
				       X25_MASK_THROUGHPUT |
				       X25_MASK_PACKET_SIZE |
				       X25_MASK_WINDOW_SIZE;
	nb->t20      = sysctl_x25_restart_request_timeout;
	refcount_set(&nb->refcnt, 1);

	write_lock_bh(&x25_neigh_list_lock);
	list_add(&nb->node, &x25_neigh_list);
	write_unlock_bh(&x25_neigh_list_lock);
}