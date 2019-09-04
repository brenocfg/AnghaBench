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
struct at91wdt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_WDT_CR ; 
 int AT91_WDT_KEY ; 
 int AT91_WDT_WDRSTT ; 
 int /*<<< orphan*/  wdt_write (struct at91wdt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void at91_wdt_reset(struct at91wdt *wdt)
{
	wdt_write(wdt, AT91_WDT_CR, AT91_WDT_KEY | AT91_WDT_WDRSTT);
}