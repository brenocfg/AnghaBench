#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {scalar_t__ stype; int /*<<< orphan*/  all_alarms; } ;
struct TYPE_9__ {int rrdcalc_flags; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  hostname; } ;
typedef  scalar_t__ SILENCE_TYPE ;
typedef  TYPE_1__ RRDHOST ;
typedef  TYPE_2__ RRDCALC ;

/* Variables and functions */
 int RRDCALC_FLAG_DISABLED ; 
 int RRDCALC_FLAG_SILENCED ; 
 scalar_t__ STYPE_DISABLE_ALARMS ; 
 scalar_t__ STYPE_SILENCE_NOTIFICATIONS ; 
 scalar_t__ check_silenced (TYPE_2__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 TYPE_5__* silencers ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int update_disabled_silenced(RRDHOST *host, RRDCALC *rc) {
    uint32_t rrdcalc_flags_old = rc->rrdcalc_flags;
    // Clear the flags
    rc->rrdcalc_flags &= ~(RRDCALC_FLAG_DISABLED | RRDCALC_FLAG_SILENCED);
    if (unlikely(silencers->all_alarms)) {
        if (silencers->stype == STYPE_DISABLE_ALARMS) rc->rrdcalc_flags |= RRDCALC_FLAG_DISABLED;
        else if (silencers->stype == STYPE_SILENCE_NOTIFICATIONS) rc->rrdcalc_flags |= RRDCALC_FLAG_SILENCED;
    } else {
        SILENCE_TYPE st = check_silenced(rc, host->hostname, silencers);
        if (st == STYPE_DISABLE_ALARMS) rc->rrdcalc_flags |= RRDCALC_FLAG_DISABLED;
        else if (st == STYPE_SILENCE_NOTIFICATIONS) rc->rrdcalc_flags |= RRDCALC_FLAG_SILENCED;
    }

    if (rrdcalc_flags_old != rc->rrdcalc_flags) {
        info("Alarm silencing changed for host '%s' alarm '%s': Disabled %s->%s Silenced %s->%s",
             host->hostname,
             rc->name,
             (rrdcalc_flags_old & RRDCALC_FLAG_DISABLED)?"true":"false",
             (rc->rrdcalc_flags & RRDCALC_FLAG_DISABLED)?"true":"false",
             (rrdcalc_flags_old & RRDCALC_FLAG_SILENCED)?"true":"false",
             (rc->rrdcalc_flags & RRDCALC_FLAG_SILENCED)?"true":"false"
        );
    }
    if (rc->rrdcalc_flags & RRDCALC_FLAG_DISABLED)
        return 1;
    else
        return 0;
}