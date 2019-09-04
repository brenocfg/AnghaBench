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
 int /*<<< orphan*/  gsc_writel (int,unsigned long) ; 
 int lasi_power_off_hpa ; 

__attribute__((used)) static void lasi_power_off(void)
{
	unsigned long datareg;

	/* calculate addr of the Power Control Register */
	datareg = lasi_power_off_hpa + 0x0000C000;

	/* Power down the machine */
	gsc_writel(0x02, datareg);
}