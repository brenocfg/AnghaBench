#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int stalled; } ;
struct ast_vhub_ep {TYPE_3__ epn; } ;
struct TYPE_8__ {scalar_t__ speed; } ;
struct ast_vhub_dev {int suspended; int wakeup_en; struct ast_vhub_ep** epns; TYPE_2__* vhub; TYPE_4__ gadget; TYPE_1__* driver; int /*<<< orphan*/  enabled; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reset ) (TYPE_4__*) ;} ;

/* Variables and functions */
 unsigned int AST_VHUB_NUM_GEN_EPs ; 
 int /*<<< orphan*/  DDBG (struct ast_vhub_dev*,char*) ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  ast_vhub_dev_disable (struct ast_vhub_dev*) ; 
 int /*<<< orphan*/  ast_vhub_dev_enable (struct ast_vhub_dev*) ; 
 int /*<<< orphan*/  ast_vhub_update_epn_stall (struct ast_vhub_ep*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

void ast_vhub_dev_reset(struct ast_vhub_dev *d)
{
	/*
	 * If speed is not set, we enable the port. If it is,
	 * send reset to the gadget and reset "speed".
	 *
	 * Speed is an indication that we have got the first
	 * setup packet to the device.
	 */
	if (d->gadget.speed == USB_SPEED_UNKNOWN && !d->enabled) {
		DDBG(d, "Reset at unknown speed of disabled device, enabling...\n");
		ast_vhub_dev_enable(d);
		d->suspended = false;
	}
	if (d->gadget.speed != USB_SPEED_UNKNOWN && d->driver) {
		unsigned int i;

		DDBG(d, "Reset at known speed of bound device, resetting...\n");
		spin_unlock(&d->vhub->lock);
		d->driver->reset(&d->gadget);
		spin_lock(&d->vhub->lock);

		/*
		 * Disable/re-enable HW, this will clear the address
		 * and speed setting.
		 */
		ast_vhub_dev_disable(d);
		ast_vhub_dev_enable(d);

		/* Clear stall on all EPs */
		for (i = 0; i < AST_VHUB_NUM_GEN_EPs; i++) {
			struct ast_vhub_ep *ep = d->epns[i];

			if (ep && ep->epn.stalled) {
				ep->epn.stalled = false;
				ast_vhub_update_epn_stall(ep);
			}
		}

		/* Additional cleanups */
		d->wakeup_en = false;
		d->suspended = false;
	}
}