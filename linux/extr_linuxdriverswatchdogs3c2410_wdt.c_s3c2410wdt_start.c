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
struct s3c2410_wdt {unsigned long count; int /*<<< orphan*/  lock; scalar_t__ reg_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ S3C2410_WTCNT ; 
 scalar_t__ S3C2410_WTCON ; 
 unsigned long S3C2410_WTCON_DIV128 ; 
 unsigned long S3C2410_WTCON_ENABLE ; 
 unsigned long S3C2410_WTCON_INTEN ; 
 unsigned long S3C2410_WTCON_RSTEN ; 
 scalar_t__ S3C2410_WTDAT ; 
 int /*<<< orphan*/  __s3c2410wdt_stop (struct s3c2410_wdt*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 unsigned long readl (scalar_t__) ; 
 scalar_t__ soft_noboot ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct s3c2410_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int s3c2410wdt_start(struct watchdog_device *wdd)
{
	unsigned long wtcon;
	struct s3c2410_wdt *wdt = watchdog_get_drvdata(wdd);

	spin_lock(&wdt->lock);

	__s3c2410wdt_stop(wdt);

	wtcon = readl(wdt->reg_base + S3C2410_WTCON);
	wtcon |= S3C2410_WTCON_ENABLE | S3C2410_WTCON_DIV128;

	if (soft_noboot) {
		wtcon |= S3C2410_WTCON_INTEN;
		wtcon &= ~S3C2410_WTCON_RSTEN;
	} else {
		wtcon &= ~S3C2410_WTCON_INTEN;
		wtcon |= S3C2410_WTCON_RSTEN;
	}

	dev_dbg(wdt->dev, "Starting watchdog: count=0x%08x, wtcon=%08lx\n",
		wdt->count, wtcon);

	writel(wdt->count, wdt->reg_base + S3C2410_WTDAT);
	writel(wdt->count, wdt->reg_base + S3C2410_WTCNT);
	writel(wtcon, wdt->reg_base + S3C2410_WTCON);
	spin_unlock(&wdt->lock);

	return 0;
}