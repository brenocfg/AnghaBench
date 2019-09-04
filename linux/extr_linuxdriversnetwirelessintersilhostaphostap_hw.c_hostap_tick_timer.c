#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_6__ {int expires; } ;
struct TYPE_5__ {int last_tick_timer; int last_comms_qual_update; scalar_t__ iw_mode; TYPE_4__ tick_timer; int /*<<< orphan*/  comms_qual_update; int /*<<< orphan*/  dev; scalar_t__ dev_enabled; int /*<<< orphan*/  hw_resetting; scalar_t__ hw_ready; int /*<<< orphan*/  hw_downloading; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  HFA384X_CMDCODE_INQUIRE ; 
 int /*<<< orphan*/  HFA384X_INFO_COMMTALLIES ; 
 int HZ ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  add_timer (TYPE_4__*) ; 
 TYPE_1__* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfa384x_cmd_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int jiffies ; 
 TYPE_1__* local ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_timer ; 
 scalar_t__ time_after (int,int) ; 

__attribute__((used)) static void hostap_tick_timer(struct timer_list *t)
{
	static unsigned long last_inquire = 0;
	local_info_t *local = from_timer(local, t, tick_timer);
	local->last_tick_timer = jiffies;

	/* Inquire CommTallies every 10 seconds to keep the statistics updated
	 * more often during low load and when using 32-bit tallies. */
	if ((!last_inquire || time_after(jiffies, last_inquire + 10 * HZ)) &&
	    !local->hw_downloading && local->hw_ready &&
	    !local->hw_resetting && local->dev_enabled) {
		hfa384x_cmd_callback(local->dev, HFA384X_CMDCODE_INQUIRE,
				     HFA384X_INFO_COMMTALLIES, NULL, 0);
		last_inquire = jiffies;
	}

	if ((local->last_comms_qual_update == 0 ||
	     time_after(jiffies, local->last_comms_qual_update + 10 * HZ)) &&
	    (local->iw_mode == IW_MODE_INFRA ||
	     local->iw_mode == IW_MODE_ADHOC)) {
		schedule_work(&local->comms_qual_update);
	}

	local->tick_timer.expires = jiffies + 2 * HZ;
	add_timer(&local->tick_timer);
}