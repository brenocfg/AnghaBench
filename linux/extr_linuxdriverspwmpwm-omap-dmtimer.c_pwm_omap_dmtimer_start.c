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
struct pwm_omap_dmtimer_chip {int /*<<< orphan*/  dm_timer; TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_counter ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* enable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DM_TIMER_LOAD_MIN ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pwm_omap_dmtimer_start(struct pwm_omap_dmtimer_chip *omap)
{
	/*
	 * According to OMAP 4 TRM section 22.2.4.10 the counter should be
	 * started at 0xFFFFFFFE when overflow and match is used to ensure
	 * that the PWM line is toggled on the first event.
	 *
	 * Note that omap_dm_timer_enable/disable is for register access and
	 * not the timer counter itself.
	 */
	omap->pdata->enable(omap->dm_timer);
	omap->pdata->write_counter(omap->dm_timer, DM_TIMER_LOAD_MIN);
	omap->pdata->disable(omap->dm_timer);

	omap->pdata->start(omap->dm_timer);
}