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
struct hso_serial {int /*<<< orphan*/  serial_lock; TYPE_1__* parent; } ;
struct TYPE_2__ {int port_spec; } ;

/* Variables and functions */
 int HSO_INTF_MUX ; 
 int /*<<< orphan*/  put_rxbuf_data_and_resubmit_bulk_urb (struct hso_serial*) ; 
 int /*<<< orphan*/  put_rxbuf_data_and_resubmit_ctrl_urb (struct hso_serial*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hso_unthrottle_tasklet(struct hso_serial *serial)
{
	unsigned long flags;

	spin_lock_irqsave(&serial->serial_lock, flags);
	if ((serial->parent->port_spec & HSO_INTF_MUX))
		put_rxbuf_data_and_resubmit_ctrl_urb(serial);
	else
		put_rxbuf_data_and_resubmit_bulk_urb(serial);
	spin_unlock_irqrestore(&serial->serial_lock, flags);
}