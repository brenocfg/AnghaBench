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
typedef  scalar_t__ u64 ;
struct fw_unit {int dummy; } ;
struct delayed_work {int dummy; } ;
struct TYPE_4__ {TYPE_1__* card; } ;
struct TYPE_3__ {scalar_t__ reset_jiffies; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROBE_DELAY_MS ; 
 TYPE_2__* fw_parent_device (struct fw_unit*) ; 
 scalar_t__ get_jiffies_64 () ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,struct delayed_work*,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 
 scalar_t__ time_after64 (scalar_t__,scalar_t__) ; 

void snd_fw_schedule_registration(struct fw_unit *unit,
				  struct delayed_work *dwork)
{
	u64 now, delay;

	now = get_jiffies_64();
	delay = fw_parent_device(unit)->card->reset_jiffies
					+ msecs_to_jiffies(PROBE_DELAY_MS);

	if (time_after64(delay, now))
		delay -= now;
	else
		delay = 0;

	mod_delayed_work(system_wq, dwork, delay);
}