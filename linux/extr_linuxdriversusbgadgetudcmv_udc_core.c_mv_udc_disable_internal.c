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
struct mv_udc {scalar_t__ active; int /*<<< orphan*/  phy_regs; TYPE_2__* pdata; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* phy_deinit ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_clock_disable (struct mv_udc*) ; 

__attribute__((used)) static void mv_udc_disable_internal(struct mv_udc *udc)
{
	if (udc->active) {
		dev_dbg(&udc->dev->dev, "disable udc\n");
		if (udc->pdata->phy_deinit)
			udc->pdata->phy_deinit(udc->phy_regs);
		udc_clock_disable(udc);
		udc->active = 0;
	}
}