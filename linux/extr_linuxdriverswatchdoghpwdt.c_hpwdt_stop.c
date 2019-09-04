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
 int /*<<< orphan*/  hpwdt_timer_con ; 
 unsigned long ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void hpwdt_stop(void)
{
	unsigned long data;

	pr_debug("stop  watchdog\n");

	data = ioread8(hpwdt_timer_con);
	data &= 0xFE;
	iowrite8(data, hpwdt_timer_con);
}