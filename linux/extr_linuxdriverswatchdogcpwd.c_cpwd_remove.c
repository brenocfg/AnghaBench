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
struct platform_device {int /*<<< orphan*/ * resource; } ;
struct cpwd {int /*<<< orphan*/  regs; int /*<<< orphan*/  irq; scalar_t__ initialized; scalar_t__ broken; TYPE_1__* devs; int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {int runstatus; int /*<<< orphan*/  misc; } ;

/* Variables and functions */
 int WD_NUMDEVS ; 
 int WD_STAT_BSTOP ; 
 int WD_TIMER_REGSZ ; 
 int /*<<< orphan*/ * cpwd_device ; 
 int /*<<< orphan*/  cpwd_resetbrokentimer (struct cpwd*,int) ; 
 int /*<<< orphan*/  cpwd_stoptimer (struct cpwd*,int) ; 
 int /*<<< orphan*/  cpwd_timer ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cpwd*) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct cpwd* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cpwd_remove(struct platform_device *op)
{
	struct cpwd *p = platform_get_drvdata(op);
	int i;

	for (i = 0; i < WD_NUMDEVS; i++) {
		misc_deregister(&p->devs[i].misc);

		if (!p->enabled) {
			cpwd_stoptimer(p, i);
			if (p->devs[i].runstatus & WD_STAT_BSTOP)
				cpwd_resetbrokentimer(p, i);
		}
	}

	if (p->broken)
		del_timer_sync(&cpwd_timer);

	if (p->initialized)
		free_irq(p->irq, p);

	of_iounmap(&op->resource[0], p->regs, 4 * WD_TIMER_REGSZ);

	cpwd_device = NULL;

	return 0;
}