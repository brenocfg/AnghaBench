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
 int /*<<< orphan*/  EPXC3_WATCHDOG_CTL_REG ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static void epx_c3_stop(void)
{

	outb(0, EPXC3_WATCHDOG_CTL_REG);

	pr_info("Stopped watchdog timer\n");
}