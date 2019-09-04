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
struct watchdog_device {int timeout; } ;

/* Variables and functions */
 int COUNT_ENAB ; 
 int DEBUG_EN ; 
 int MATCH_INT ; 
 int MATCH_OUTPUT_HIGH ; 
 int M_RES2 ; 
 int RESET_COUNT ; 
 int RESET_COUNT0 ; 
 int STOP_COUNT0 ; 
 int WDOG_COUNTER_RATE ; 
 int /*<<< orphan*/  WDTIM_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_EMR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_MATCH0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_MCTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTIM_PULSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  io_lock ; 
 scalar_t__ readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_base ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pnx4008_wdt_start(struct watchdog_device *wdd)
{
	spin_lock(&io_lock);

	/* stop counter, initiate counter reset */
	writel(RESET_COUNT, WDTIM_CTRL(wdt_base));
	/*wait for reset to complete. 100% guarantee event */
	while (readl(WDTIM_COUNTER(wdt_base)))
		cpu_relax();
	/* internal and external reset, stop after that */
	writel(M_RES2 | STOP_COUNT0 | RESET_COUNT0, WDTIM_MCTRL(wdt_base));
	/* configure match output */
	writel(MATCH_OUTPUT_HIGH, WDTIM_EMR(wdt_base));
	/* clear interrupt, just in case */
	writel(MATCH_INT, WDTIM_INT(wdt_base));
	/* the longest pulse period 65541/(13*10^6) seconds ~ 5 ms. */
	writel(0xFFFF, WDTIM_PULSE(wdt_base));
	writel(wdd->timeout * WDOG_COUNTER_RATE, WDTIM_MATCH0(wdt_base));
	/*enable counter, stop when debugger active */
	writel(COUNT_ENAB | DEBUG_EN, WDTIM_CTRL(wdt_base));

	spin_unlock(&io_lock);
	return 0;
}