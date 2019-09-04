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
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DWC_ALLOC (int) ; 

dwc_otg_hcd_t *dwc_otg_hcd_alloc_hcd(void)
{
	return DWC_ALLOC(sizeof(dwc_otg_hcd_t));
}