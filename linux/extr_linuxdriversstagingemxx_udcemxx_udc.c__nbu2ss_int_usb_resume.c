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
struct nbu2ss_udc {int usb_suspended; int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; TYPE_1__* driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void _nbu2ss_int_usb_resume(struct nbu2ss_udc *udc)
{
	if (udc->usb_suspended == 1) {
		udc->usb_suspended = 0;
		if (udc->driver && udc->driver->resume) {
			spin_unlock(&udc->lock);
			udc->driver->resume(&udc->gadget);
			spin_lock(&udc->lock);
		}
	}
}