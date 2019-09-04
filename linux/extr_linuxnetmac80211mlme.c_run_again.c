#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  expires; } ;
struct TYPE_5__ {TYPE_3__ timer; } ;
struct TYPE_6__ {TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_timer (TYPE_3__*,unsigned long) ; 
 int /*<<< orphan*/  sdata_assert_lock (struct ieee80211_sub_if_data*) ; 
 scalar_t__ time_before (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_pending (TYPE_3__*) ; 

__attribute__((used)) static void run_again(struct ieee80211_sub_if_data *sdata,
		      unsigned long timeout)
{
	sdata_assert_lock(sdata);

	if (!timer_pending(&sdata->u.mgd.timer) ||
	    time_before(timeout, sdata->u.mgd.timer.expires))
		mod_timer(&sdata->u.mgd.timer, timeout);
}