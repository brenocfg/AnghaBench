#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_8__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_10__ {int counter_done; int update_every; TYPE_1__ last_collected_time; } ;
struct TYPE_9__ {char* chart; scalar_t__ next_update; scalar_t__ before; scalar_t__ after; int /*<<< orphan*/  name; TYPE_3__* rrdset; int /*<<< orphan*/  update_every; } ;
typedef  TYPE_2__ RRDCALC ;

/* Variables and functions */
 int /*<<< orphan*/  D_HEALTH ; 
 scalar_t__ RRDCALC_HAS_DB_LOOKUP (TYPE_2__*) ; 
 int /*<<< orphan*/  RRDSET_FLAG_ENABLED ; 
 int /*<<< orphan*/  RRDSET_FLAG_OBSOLETE ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ rrdset_first_entry_t (TYPE_3__*) ; 
 int rrdset_flag_check (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ rrdset_last_entry_t (TYPE_3__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int rrdcalc_isrunnable(RRDCALC *rc, time_t now, time_t *next_run) {
    if(unlikely(!rc->rrdset)) {
        debug(D_HEALTH, "Health not running alarm '%s.%s'. It is not linked to a chart.", rc->chart?rc->chart:"NOCHART", rc->name);
        return 0;
    }

    if(unlikely(rc->next_update > now)) {
        if (unlikely(*next_run > rc->next_update)) {
            // update the next_run time of the main loop
            // to run this alarm precisely the time required
            *next_run = rc->next_update;
        }

        debug(D_HEALTH, "Health not examining alarm '%s.%s' yet (will do in %d secs).", rc->chart?rc->chart:"NOCHART", rc->name, (int) (rc->next_update - now));
        return 0;
    }

    if(unlikely(!rc->update_every)) {
        debug(D_HEALTH, "Health not running alarm '%s.%s'. It does not have an update frequency", rc->chart?rc->chart:"NOCHART", rc->name);
        return 0;
    }

    if(unlikely(rrdset_flag_check(rc->rrdset, RRDSET_FLAG_OBSOLETE))) {
        debug(D_HEALTH, "Health not running alarm '%s.%s'. The chart has been marked as obsolete", rc->chart?rc->chart:"NOCHART", rc->name);
        return 0;
    }

    if(unlikely(!rrdset_flag_check(rc->rrdset, RRDSET_FLAG_ENABLED))) {
        debug(D_HEALTH, "Health not running alarm '%s.%s'. The chart is not enabled", rc->chart?rc->chart:"NOCHART", rc->name);
        return 0;
    }

    if(unlikely(!rc->rrdset->last_collected_time.tv_sec || rc->rrdset->counter_done < 2)) {
        debug(D_HEALTH, "Health not running alarm '%s.%s'. Chart is not fully collected yet.", rc->chart?rc->chart:"NOCHART", rc->name);
        return 0;
    }

    int update_every = rc->rrdset->update_every;
    time_t first = rrdset_first_entry_t(rc->rrdset);
    time_t last = rrdset_last_entry_t(rc->rrdset);

    if(unlikely(now + update_every < first /* || now - update_every > last */)) {
        debug(D_HEALTH
              , "Health not examining alarm '%s.%s' yet (wanted time is out of bounds - we need %lu but got %lu - %lu)."
              , rc->chart ? rc->chart : "NOCHART", rc->name, (unsigned long) now, (unsigned long) first
              , (unsigned long) last);
        return 0;
    }

    if(RRDCALC_HAS_DB_LOOKUP(rc)) {
        time_t needed = now + rc->before + rc->after;

        if(needed + update_every < first || needed - update_every > last) {
            debug(D_HEALTH
                  , "Health not examining alarm '%s.%s' yet (not enough data yet - we need %lu but got %lu - %lu)."
                  , rc->chart ? rc->chart : "NOCHART", rc->name, (unsigned long) needed, (unsigned long) first
                  , (unsigned long) last);
            return 0;
        }
    }

    return 1;
}