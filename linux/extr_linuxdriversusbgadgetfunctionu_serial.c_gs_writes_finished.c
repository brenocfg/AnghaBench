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
struct gs_port {int /*<<< orphan*/  port_lock; int /*<<< orphan*/  port_write_buf; int /*<<< orphan*/ * port_usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfifo_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gs_writes_finished(struct gs_port *p)
{
	int cond;

	/* return true on disconnect or empty buffer */
	spin_lock_irq(&p->port_lock);
	cond = (p->port_usb == NULL) || !kfifo_len(&p->port_write_buf);
	spin_unlock_irq(&p->port_lock);

	return cond;
}