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
struct hc_driver {scalar_t__ port_power; scalar_t__ reset; int /*<<< orphan*/  hcd_priv_size; } ;
struct ehci_driver_overrides {scalar_t__ port_power; scalar_t__ reset; scalar_t__ extra_priv_size; } ;

/* Variables and functions */
 struct hc_driver ehci_hc_driver ; 

void ehci_init_driver(struct hc_driver *drv,
		const struct ehci_driver_overrides *over)
{
	/* Copy the generic table to drv and then apply the overrides */
	*drv = ehci_hc_driver;

	if (over) {
		drv->hcd_priv_size += over->extra_priv_size;
		if (over->reset)
			drv->reset = over->reset;
		if (over->port_power)
			drv->port_power = over->port_power;
	}
}