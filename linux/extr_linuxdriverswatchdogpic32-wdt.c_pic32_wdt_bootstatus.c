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
typedef  int u32 ;
struct pic32_wdt {int /*<<< orphan*/  rst_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC32_CLR (int /*<<< orphan*/ ) ; 
 int RESETCON_WDT_TIMEOUT ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pic32_wdt_bootstatus(struct pic32_wdt *wdt)
{
	u32 v = readl(wdt->rst_base);

	writel(RESETCON_WDT_TIMEOUT, PIC32_CLR(wdt->rst_base));

	return v & RESETCON_WDT_TIMEOUT;
}