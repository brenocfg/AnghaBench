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
struct vnet_port {int /*<<< orphan*/  clean_timer; } ;
struct timer_list {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 scalar_t__ VNET_CLEAN_TIMEOUT ; 
 int /*<<< orphan*/  VNET_PORT_TO_NET_DEVICE (struct vnet_port*) ; 
 int /*<<< orphan*/  clean_timer ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct vnet_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_tx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_unlock (int /*<<< orphan*/ ) ; 
 struct vnet_port* port ; 
 struct sk_buff* vnet_clean_tx_ring (struct vnet_port*,unsigned int*) ; 
 int /*<<< orphan*/  vnet_free_skbs (struct sk_buff*) ; 

void sunvnet_clean_timer_expire_common(struct timer_list *t)
{
	struct vnet_port *port = from_timer(port, t, clean_timer);
	struct sk_buff *freeskbs;
	unsigned pending;

	netif_tx_lock(VNET_PORT_TO_NET_DEVICE(port));
	freeskbs = vnet_clean_tx_ring(port, &pending);
	netif_tx_unlock(VNET_PORT_TO_NET_DEVICE(port));

	vnet_free_skbs(freeskbs);

	if (pending)
		(void)mod_timer(&port->clean_timer,
				jiffies + VNET_CLEAN_TIMEOUT);
	 else
		del_timer(&port->clean_timer);
}