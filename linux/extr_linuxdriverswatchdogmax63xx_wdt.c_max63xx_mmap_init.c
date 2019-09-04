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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct max63xx_wdt {int /*<<< orphan*/  set; int /*<<< orphan*/  ping; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  max63xx_mmap_ping ; 
 int /*<<< orphan*/  max63xx_mmap_set ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max63xx_mmap_init(struct platform_device *p, struct max63xx_wdt *wdt)
{
	struct resource *mem = platform_get_resource(p, IORESOURCE_MEM, 0);

	wdt->base = devm_ioremap_resource(&p->dev, mem);
	if (IS_ERR(wdt->base))
		return PTR_ERR(wdt->base);

	spin_lock_init(&wdt->lock);

	wdt->ping = max63xx_mmap_ping;
	wdt->set = max63xx_mmap_set;
	return 0;
}