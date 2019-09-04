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
 scalar_t__ WDTCON_REG ; 
 int WDTCON_WIN_EN ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline bool pic32_wdt_is_win_enabled(struct pic32_wdt *wdt)
{
	return !!(readl(wdt->regs + WDTCON_REG) & WDTCON_WIN_EN);
}