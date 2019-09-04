#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ state; } ;
struct isp1760_udc {TYPE_2__ gadget; TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* suspend ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ USB_STATE_DEFAULT ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void isp1760_udc_suspend(struct isp1760_udc *udc)
{
	if (udc->gadget.state < USB_STATE_DEFAULT)
		return;

	if (udc->driver->suspend)
		udc->driver->suspend(&udc->gadget);
}