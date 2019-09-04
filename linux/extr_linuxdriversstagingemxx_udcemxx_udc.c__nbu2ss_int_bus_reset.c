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
struct nbu2ss_udc {int /*<<< orphan*/  ep0state; scalar_t__ remote_wakeup; int /*<<< orphan*/  devstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP0_IDLE ; 
 int /*<<< orphan*/  USB_STATE_DEFAULT ; 
 int /*<<< orphan*/  _nbu2ss_quiesce (struct nbu2ss_udc*) ; 

__attribute__((used)) static inline void _nbu2ss_int_bus_reset(struct nbu2ss_udc *udc)
{
	udc->devstate		= USB_STATE_DEFAULT;
	udc->remote_wakeup	= 0;

	_nbu2ss_quiesce(udc);

	udc->ep0state = EP0_IDLE;
}