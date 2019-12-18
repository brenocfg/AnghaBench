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
struct wm_adsp {int /*<<< orphan*/  pwr_lock; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* stop_watchdog ) (struct wm_adsp*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  adsp_warn (struct wm_adsp*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct wm_adsp*) ; 
 int /*<<< orphan*/  wm_adsp_fatal_error (struct wm_adsp*) ; 

irqreturn_t wm_halo_wdt_expire(int irq, void *data)
{
	struct wm_adsp *dsp = data;

	mutex_lock(&dsp->pwr_lock);

	adsp_warn(dsp, "WDT Expiry Fault\n");
	dsp->ops->stop_watchdog(dsp);
	wm_adsp_fatal_error(dsp);

	mutex_unlock(&dsp->pwr_lock);

	return IRQ_HANDLED;
}