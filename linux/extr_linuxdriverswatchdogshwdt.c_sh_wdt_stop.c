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
typedef  int /*<<< orphan*/  u8 ;
struct watchdog_device {int dummy; } ;
struct sh_wdt {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WTCSR_TME ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_wdt_read_csr () ; 
 int /*<<< orphan*/  sh_wdt_write_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sh_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int sh_wdt_stop(struct watchdog_device *wdt_dev)
{
	struct sh_wdt *wdt = watchdog_get_drvdata(wdt_dev);
	unsigned long flags;
	u8 csr;

	spin_lock_irqsave(&wdt->lock, flags);

	del_timer(&wdt->timer);

	csr = sh_wdt_read_csr();
	csr &= ~WTCSR_TME;
	sh_wdt_write_csr(csr);

	spin_unlock_irqrestore(&wdt->lock, flags);

	clk_disable(wdt->clk);
	pm_runtime_put_sync(wdt->dev);

	return 0;
}