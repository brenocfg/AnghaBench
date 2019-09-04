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
struct TYPE_2__ {unsigned int vbus_active_low; } ;
struct at91_udc {unsigned int vbus; int /*<<< orphan*/  gadget; TYPE_1__ board; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_vbus_session (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void at91_vbus_update(struct at91_udc *udc, unsigned value)
{
	value ^= udc->board.vbus_active_low;
	if (value != udc->vbus)
		at91_vbus_session(&udc->gadget, value);
}