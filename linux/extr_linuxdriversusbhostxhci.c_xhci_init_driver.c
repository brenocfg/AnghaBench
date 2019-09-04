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
struct xhci_driver_overrides {scalar_t__ start; scalar_t__ reset; scalar_t__ extra_priv_size; } ;
struct hc_driver {scalar_t__ start; scalar_t__ reset; int /*<<< orphan*/  hcd_priv_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct hc_driver xhci_hc_driver ; 

void xhci_init_driver(struct hc_driver *drv,
		      const struct xhci_driver_overrides *over)
{
	BUG_ON(!over);

	/* Copy the generic table to drv then apply the overrides */
	*drv = xhci_hc_driver;

	if (over) {
		drv->hcd_priv_size += over->extra_priv_size;
		if (over->reset)
			drv->reset = over->reset;
		if (over->start)
			drv->start = over->start;
	}
}