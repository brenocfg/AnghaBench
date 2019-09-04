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
struct pardevice {int waiting; int /*<<< orphan*/  wait_q; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  current ; 
 int parport_claim (struct pardevice*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int parport_claim_or_block(struct pardevice *dev)
{
	int r;

	/*
	 * Signal to parport_claim() that we can wait even without a
	 * wakeup function.
	 */
	dev->waiting = 2;

	/* Try to claim the port.  If this fails, we need to sleep.  */
	r = parport_claim(dev);
	if (r == -EAGAIN) {
#ifdef PARPORT_DEBUG_SHARING
		printk(KERN_DEBUG "%s: parport_claim() returned -EAGAIN\n", dev->name);
#endif
		/*
		 * FIXME!!! Use the proper locking for dev->waiting,
		 * and make this use the "wait_event_interruptible()"
		 * interfaces. The cli/sti that used to be here
		 * did nothing.
		 *
		 * See also parport_release()
		 */

		/*
		 * If dev->waiting is clear now, an interrupt
		 * gave us the port and we would deadlock if we slept.
		 */
		if (dev->waiting) {
			wait_event_interruptible(dev->wait_q,
						 !dev->waiting);
			if (signal_pending(current))
				return -EINTR;
			r = 1;
		} else {
			r = 0;
#ifdef PARPORT_DEBUG_SHARING
			printk(KERN_DEBUG "%s: didn't sleep in parport_claim_or_block()\n",
			       dev->name);
#endif
		}

#ifdef PARPORT_DEBUG_SHARING
		if (dev->port->physport->cad != dev)
			printk(KERN_DEBUG "%s: exiting parport_claim_or_block but %s owns port!\n",
			       dev->name, dev->port->physport->cad ?
			       dev->port->physport->cad->name:"nobody");
#endif
	}
	dev->waiting = 0;
	return r;
}