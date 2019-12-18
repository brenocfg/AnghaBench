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
struct sta32x_priv {int shutdown; int /*<<< orphan*/  watchdog_work; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ needs_esd_watchdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sta32x_watchdog_stop(struct sta32x_priv *sta32x)
{
	if (sta32x->pdata->needs_esd_watchdog) {
		sta32x->shutdown = 1;
		cancel_delayed_work_sync(&sta32x->watchdog_work);
	}
}