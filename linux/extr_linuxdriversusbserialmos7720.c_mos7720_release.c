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
struct usb_serial {TYPE_1__** port; } ;
struct TYPE_2__ {int /*<<< orphan*/  interrupt_in_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mos7720_release(struct usb_serial *serial)
{
	usb_kill_urb(serial->port[0]->interrupt_in_urb);

#ifdef CONFIG_USB_SERIAL_MOS7715_PARPORT
	/* close the parallel port */

	if (le16_to_cpu(serial->dev->descriptor.idProduct)
	    == MOSCHIP_DEVICE_ID_7715) {
		struct urbtracker *urbtrack;
		unsigned long flags;
		struct mos7715_parport *mos_parport =
			usb_get_serial_data(serial);

		/* prevent NULL ptr dereference in port callbacks */
		spin_lock(&release_lock);
		mos_parport->pp->private_data = NULL;
		spin_unlock(&release_lock);

		/* wait for synchronous usb calls to return */
		if (mos_parport->msg_pending)
			wait_for_completion_timeout(&mos_parport->syncmsg_compl,
					    msecs_to_jiffies(MOS_WDR_TIMEOUT));

		parport_remove_port(mos_parport->pp);
		usb_set_serial_data(serial, NULL);
		mos_parport->serial = NULL;

		/* if tasklet currently scheduled, wait for it to complete */
		tasklet_kill(&mos_parport->urb_tasklet);

		/* unlink any urbs sent by the tasklet  */
		spin_lock_irqsave(&mos_parport->listlock, flags);
		list_for_each_entry(urbtrack,
				    &mos_parport->active_urbs,
				    urblist_entry)
			usb_unlink_urb(urbtrack->urb);
		spin_unlock_irqrestore(&mos_parport->listlock, flags);
		parport_del_port(mos_parport->pp);

		kref_put(&mos_parport->ref_count, destroy_mos_parport);
	}
#endif
}