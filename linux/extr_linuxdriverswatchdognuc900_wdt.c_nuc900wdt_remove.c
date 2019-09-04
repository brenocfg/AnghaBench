#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wdt_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 TYPE_1__* nuc900_wdt ; 
 int /*<<< orphan*/  nuc900wdt_miscdev ; 

__attribute__((used)) static int nuc900wdt_remove(struct platform_device *pdev)
{
	misc_deregister(&nuc900wdt_miscdev);

	clk_disable(nuc900_wdt->wdt_clock);

	return 0;
}