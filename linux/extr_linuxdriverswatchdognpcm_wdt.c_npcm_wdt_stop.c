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
struct watchdog_device {int dummy; } ;
struct npcm_wdt {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 struct npcm_wdt* to_npcm_wdt (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int npcm_wdt_stop(struct watchdog_device *wdd)
{
	struct npcm_wdt *wdt = to_npcm_wdt(wdd);

	writel(0, wdt->reg);

	return 0;
}