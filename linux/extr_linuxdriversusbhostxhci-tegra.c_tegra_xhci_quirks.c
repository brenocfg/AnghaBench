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
struct xhci_hcd {int /*<<< orphan*/  quirks; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XHCI_PLAT ; 

__attribute__((used)) static void tegra_xhci_quirks(struct device *dev, struct xhci_hcd *xhci)
{
	xhci->quirks |= XHCI_PLAT;
}