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
struct xdp_umem {int /*<<< orphan*/  xsk_list_lock; int /*<<< orphan*/  xsk_list; } ;
struct xdp_sock {int /*<<< orphan*/  list; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void xdp_add_sk_umem(struct xdp_umem *umem, struct xdp_sock *xs)
{
	unsigned long flags;

	if (!xs->tx)
		return;

	spin_lock_irqsave(&umem->xsk_list_lock, flags);
	list_add_rcu(&xs->list, &umem->xsk_list);
	spin_unlock_irqrestore(&umem->xsk_list_lock, flags);
}