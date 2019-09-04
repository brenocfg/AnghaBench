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
struct watchdog_device {int /*<<< orphan*/  timeout; } ;
struct uniphier_wdt_dev {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int __uniphier_watchdog_start (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int roundup_pow_of_two (int /*<<< orphan*/ ) ; 
 struct uniphier_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int uniphier_watchdog_start(struct watchdog_device *w)
{
	struct uniphier_wdt_dev *wdev = watchdog_get_drvdata(w);
	unsigned int tmp_timeout;

	tmp_timeout = roundup_pow_of_two(w->timeout);

	return __uniphier_watchdog_start(wdev->regmap, tmp_timeout);
}