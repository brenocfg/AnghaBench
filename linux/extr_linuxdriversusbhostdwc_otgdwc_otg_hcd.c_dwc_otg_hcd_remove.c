#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  core_if; } ;
typedef  TYPE_1__ dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  dwc_otg_disable_host_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_free (TYPE_1__*) ; 

void dwc_otg_hcd_remove(dwc_otg_hcd_t * hcd)
{
	/* Turn off all host-specific interrupts. */
	dwc_otg_disable_host_interrupts(hcd->core_if);

	dwc_otg_hcd_free(hcd);
}