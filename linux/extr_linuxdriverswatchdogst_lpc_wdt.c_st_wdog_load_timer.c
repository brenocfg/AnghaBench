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
struct st_wdog {unsigned long clkrate; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LPC_LPA_LSB_OFF ; 
 scalar_t__ LPC_LPA_START_OFF ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void st_wdog_load_timer(struct st_wdog *st_wdog, unsigned int timeout)
{
	unsigned long clkrate = st_wdog->clkrate;

	writel_relaxed(timeout * clkrate, st_wdog->base + LPC_LPA_LSB_OFF);
	writel_relaxed(1, st_wdog->base + LPC_LPA_START_OFF);
}