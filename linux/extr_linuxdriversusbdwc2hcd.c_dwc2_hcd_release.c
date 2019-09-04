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
struct dwc2_hsotg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc2_disable_host_interrupts (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_hcd_free (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_hcd_release(struct dwc2_hsotg *hsotg)
{
	/* Turn off all host-specific interrupts */
	dwc2_disable_host_interrupts(hsotg);

	dwc2_hcd_free(hsotg);
}