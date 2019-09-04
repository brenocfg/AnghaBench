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

/* Variables and functions */
 int /*<<< orphan*/  GEF_WDC_ENABLED_TRUE ; 
 int /*<<< orphan*/  GEF_WDC_SERVICE_SHIFT ; 
 int /*<<< orphan*/  gef_wdt_toggle_wdc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gef_wdt_service(void)
{
	gef_wdt_toggle_wdc(GEF_WDC_ENABLED_TRUE,
		GEF_WDC_SERVICE_SHIFT);
}