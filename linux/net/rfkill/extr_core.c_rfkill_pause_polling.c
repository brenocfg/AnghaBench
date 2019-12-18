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
struct rfkill {int polling_paused; int /*<<< orphan*/  poll_work; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

void rfkill_pause_polling(struct rfkill *rfkill)
{
	BUG_ON(!rfkill);

	if (!rfkill->ops->poll)
		return;

	rfkill->polling_paused = true;
	cancel_delayed_work_sync(&rfkill->poll_work);
}