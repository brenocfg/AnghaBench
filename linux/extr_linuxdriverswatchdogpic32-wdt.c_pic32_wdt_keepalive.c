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
struct pic32_wdt {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDTCON_CLR_KEY ; 
 scalar_t__ WDTCON_REG ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pic32_wdt_keepalive(struct pic32_wdt *wdt)
{
	/* write key through single half-word */
	writew(WDTCON_CLR_KEY, wdt->regs + WDTCON_REG + 2);
}