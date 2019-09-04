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
struct rza_wdt {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ WRCSR ; 
 int WRCSR_CLEAR_WOVF ; 
 int WRCSR_MAGIC ; 
 int WRCSR_RSTE ; 
 scalar_t__ WTCNT ; 
 int WTCNT_MAGIC ; 
 scalar_t__ WTCSR ; 
 int WTCSR_MAGIC ; 
 int WTSCR_TME ; 
 int WTSCR_WT ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 struct rza_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int rza_wdt_restart(struct watchdog_device *wdev, unsigned long action,
			    void *data)
{
	struct rza_wdt *priv = watchdog_get_drvdata(wdev);

	/* Stop timer */
	writew(WTCSR_MAGIC | 0, priv->base + WTCSR);

	/* Must dummy read WRCSR:WOVF at least once before clearing */
	readb(priv->base + WRCSR);
	writew(WRCSR_CLEAR_WOVF, priv->base + WRCSR);

	/*
	 * Start timer with fastest clock source and only 1 clock left before
	 * overflow with reset option enabled.
	 */
	writew(WRCSR_MAGIC | WRCSR_RSTE, priv->base + WRCSR);
	writew(WTCNT_MAGIC | 255, priv->base + WTCNT);
	writew(WTCSR_MAGIC | WTSCR_WT | WTSCR_TME, priv->base + WTCSR);

	/*
	 * Actually make sure the above sequence hits hardware before sleeping.
	 */
	wmb();

	/* Wait for WDT overflow (reset) */
	udelay(20);

	return 0;
}