#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;
struct sdw_intel {TYPE_2__ cdns; TYPE_1__* res; } ;
struct platform_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sdw_intel*) ; 
 struct sdw_intel* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sdw_delete_bus_master (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_remove(struct platform_device *pdev)
{
	struct sdw_intel *sdw;

	sdw = platform_get_drvdata(pdev);

	free_irq(sdw->res->irq, sdw);
	snd_soc_unregister_component(sdw->cdns.dev);
	sdw_delete_bus_master(&sdw->cdns.bus);

	return 0;
}