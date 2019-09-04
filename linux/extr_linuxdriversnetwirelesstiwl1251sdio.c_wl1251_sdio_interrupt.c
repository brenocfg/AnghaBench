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
struct wl1251 {int /*<<< orphan*/  irq_work; int /*<<< orphan*/  hw; } ;
struct sdio_func {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_IRQ ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wl1251* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wl1251_sdio_interrupt(struct sdio_func *func)
{
	struct wl1251 *wl = sdio_get_drvdata(func);

	wl1251_debug(DEBUG_IRQ, "IRQ");

	/* FIXME should be synchronous for sdio */
	ieee80211_queue_work(wl->hw, &wl->irq_work);
}