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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mv64x60_wdt_pdata {int timeout; int bus_clk; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int bus_clk ; 
 struct mv64x60_wdt_pdata* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv64x60_wdt_handler_disable () ; 
 int /*<<< orphan*/  mv64x60_wdt_miscdev ; 
 int /*<<< orphan*/ * mv64x60_wdt_regs ; 
 int /*<<< orphan*/  mv64x60_wdt_set_timeout (int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int mv64x60_wdt_probe(struct platform_device *dev)
{
	struct mv64x60_wdt_pdata *pdata = dev_get_platdata(&dev->dev);
	struct resource *r;
	int timeout = 10;

	bus_clk = 133;			/* in MHz */
	if (pdata) {
		timeout = pdata->timeout;
		bus_clk = pdata->bus_clk;
	}

	/* Since bus_clk is truncated MHz, actual frequency could be
	 * up to 1MHz higher.  Round up, since it's better to time out
	 * too late than too soon.
	 */
	bus_clk++;
	bus_clk *= 1000000;		/* convert to Hz */

	r = platform_get_resource(dev, IORESOURCE_MEM, 0);
	if (!r)
		return -ENODEV;

	mv64x60_wdt_regs = devm_ioremap(&dev->dev, r->start, resource_size(r));
	if (mv64x60_wdt_regs == NULL)
		return -ENOMEM;

	mv64x60_wdt_set_timeout(timeout);

	mv64x60_wdt_handler_disable();	/* in case timer was already running */

	return misc_register(&mv64x60_wdt_miscdev);
}