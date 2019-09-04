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
 int /*<<< orphan*/  ar7_wdt_disable (int) ; 
 int /*<<< orphan*/  ar7_wdt_kick (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void ar7_wdt_enable_wdt(void)
{
	pr_debug("enabling watchdog timer\n");
	ar7_wdt_disable(1);
	ar7_wdt_kick(1);
}