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
 unsigned long LTQ_MAX_TIMEOUT ; 
 scalar_t__ LTQ_WDT_CR ; 
 int LTQ_WDT_DIVIDER ; 
 unsigned long LTQ_WDT_PW1 ; 
 unsigned long LTQ_WDT_PW2 ; 
 unsigned long LTQ_WDT_SR_CLKDIV ; 
 unsigned long LTQ_WDT_SR_EN ; 
 unsigned long LTQ_WDT_SR_PWD ; 
 int ltq_io_region_clk_rate ; 
 int /*<<< orphan*/  ltq_w32 (unsigned long,scalar_t__) ; 
 scalar_t__ ltq_wdt_membase ; 
 int ltq_wdt_timeout ; 

__attribute__((used)) static void
ltq_wdt_enable(void)
{
	unsigned long int timeout = ltq_wdt_timeout *
			(ltq_io_region_clk_rate / LTQ_WDT_DIVIDER) + 0x1000;
	if (timeout > LTQ_MAX_TIMEOUT)
		timeout = LTQ_MAX_TIMEOUT;

	/* write the first password magic */
	ltq_w32(LTQ_WDT_PW1, ltq_wdt_membase + LTQ_WDT_CR);
	/* write the second magic plus the configuration and new timeout */
	ltq_w32(LTQ_WDT_SR_EN | LTQ_WDT_SR_PWD | LTQ_WDT_SR_CLKDIV |
		LTQ_WDT_PW2 | timeout, ltq_wdt_membase + LTQ_WDT_CR);
}