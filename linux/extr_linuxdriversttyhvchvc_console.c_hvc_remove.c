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
struct tty_struct {int dummy; } ;
struct hvc_struct {size_t index; int /*<<< orphan*/  port; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t MAX_NR_HVC_CONSOLES ; 
 int /*<<< orphan*/ ** cons_ops ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_put (int /*<<< orphan*/ *) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_vhangup (struct tty_struct*) ; 
 int* vtermnos ; 

int hvc_remove(struct hvc_struct *hp)
{
	unsigned long flags;
	struct tty_struct *tty;

	tty = tty_port_tty_get(&hp->port);

	console_lock();
	spin_lock_irqsave(&hp->lock, flags);
	if (hp->index < MAX_NR_HVC_CONSOLES) {
		vtermnos[hp->index] = -1;
		cons_ops[hp->index] = NULL;
	}

	/* Don't whack hp->irq because tty_hangup() will need to free the irq. */

	spin_unlock_irqrestore(&hp->lock, flags);
	console_unlock();

	/*
	 * We 'put' the instance that was grabbed when the kref instance
	 * was initialized using kref_init().  Let the last holder of this
	 * kref cause it to be removed, which will probably be the tty_vhangup
	 * below.
	 */
	tty_port_put(&hp->port);

	/*
	 * This function call will auto chain call hvc_hangup.
	 */
	if (tty) {
		tty_vhangup(tty);
		tty_kref_put(tty);
	}
	return 0;
}