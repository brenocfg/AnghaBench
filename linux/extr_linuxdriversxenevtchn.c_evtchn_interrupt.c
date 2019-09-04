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
struct user_evtchn {int enabled; int /*<<< orphan*/  port; struct per_user_data* user; } ;
struct per_user_data {scalar_t__ ring_prod; scalar_t__ ring_cons; scalar_t__ ring_size; int ring_overflow; int /*<<< orphan*/  ring_prod_lock; int /*<<< orphan*/  evtchn_async_queue; int /*<<< orphan*/  evtchn_wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,struct per_user_data*) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/ * evtchn_ring_entry (struct per_user_data*,scalar_t__) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static irqreturn_t evtchn_interrupt(int irq, void *data)
{
	struct user_evtchn *evtchn = data;
	struct per_user_data *u = evtchn->user;

	WARN(!evtchn->enabled,
	     "Interrupt for port %d, but apparently not enabled; per-user %p\n",
	     evtchn->port, u);

	disable_irq_nosync(irq);
	evtchn->enabled = false;

	spin_lock(&u->ring_prod_lock);

	if ((u->ring_prod - u->ring_cons) < u->ring_size) {
		*evtchn_ring_entry(u, u->ring_prod) = evtchn->port;
		wmb(); /* Ensure ring contents visible */
		if (u->ring_cons == u->ring_prod++) {
			wake_up_interruptible(&u->evtchn_wait);
			kill_fasync(&u->evtchn_async_queue,
				    SIGIO, POLL_IN);
		}
	} else
		u->ring_overflow = 1;

	spin_unlock(&u->ring_prod_lock);

	return IRQ_HANDLED;
}