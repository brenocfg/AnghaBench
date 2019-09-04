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
 int /*<<< orphan*/  IOP_WDTCR_EN ; 
 int /*<<< orphan*/  IOP_WDTCR_EN_ARM ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_lock ; 
 int /*<<< orphan*/  write_wdtcr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wdt_enable(void)
{
	/* Arm and enable the Timer to starting counting down from 0xFFFF.FFFF
	 * Takes approx. 10.7s to timeout
	 */
	spin_lock(&wdt_lock);
	write_wdtcr(IOP_WDTCR_EN_ARM);
	write_wdtcr(IOP_WDTCR_EN);
	spin_unlock(&wdt_lock);
}