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
 scalar_t__ LTQ_WDT_CR ; 
 int /*<<< orphan*/  LTQ_WDT_PW1 ; 
 int /*<<< orphan*/  LTQ_WDT_PW2 ; 
 int /*<<< orphan*/  ltq_w32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ltq_wdt_membase ; 

__attribute__((used)) static void
ltq_wdt_disable(void)
{
	/* write the first password magic */
	ltq_w32(LTQ_WDT_PW1, ltq_wdt_membase + LTQ_WDT_CR);
	/*
	 * write the second password magic with no config
	 * this turns the watchdog off
	 */
	ltq_w32(LTQ_WDT_PW2, ltq_wdt_membase + LTQ_WDT_CR);
}