#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  scalar_t__ u16 ;
typedef  int /*<<< orphan*/  gdth_ha_str ;
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/  event_string; int /*<<< orphan*/  eu; } ;
struct TYPE_6__ {scalar_t__ event_source; scalar_t__ event_idx; int same_count; scalar_t__ application; TYPE_2__ event_data; void* last_stamp; void* first_stamp; } ;
typedef  TYPE_1__ gdth_evt_str ;
typedef  TYPE_2__ gdth_evt_data ;

/* Variables and functions */
 size_t MAX_EVENTS ; 
 int /*<<< orphan*/  TRACE2 (char*) ; 
 TYPE_1__* ebuffer ; 
 size_t elastidx ; 
 size_t eoldidx ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  memcmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static gdth_evt_str *gdth_store_event(gdth_ha_str *ha, u16 source, 
                                      u16 idx, gdth_evt_data *evt)
{
    gdth_evt_str *e;

    /* no GDTH_LOCK_HA() ! */
    TRACE2(("gdth_store_event() source %d idx %d\n", source, idx));
    if (source == 0)                        /* no source -> no event */
        return NULL;

    if (ebuffer[elastidx].event_source == source &&
        ebuffer[elastidx].event_idx == idx &&
        ((evt->size != 0 && ebuffer[elastidx].event_data.size != 0 &&
            !memcmp((char *)&ebuffer[elastidx].event_data.eu,
            (char *)&evt->eu, evt->size)) ||
        (evt->size == 0 && ebuffer[elastidx].event_data.size == 0 &&
            !strcmp((char *)&ebuffer[elastidx].event_data.event_string,
            (char *)&evt->event_string)))) { 
        e = &ebuffer[elastidx];
	e->last_stamp = (u32)ktime_get_real_seconds();
        ++e->same_count;
    } else {
        if (ebuffer[elastidx].event_source != 0) {  /* entry not free ? */
            ++elastidx;
            if (elastidx == MAX_EVENTS)
                elastidx = 0;
            if (elastidx == eoldidx) {              /* reached mark ? */
                ++eoldidx;
                if (eoldidx == MAX_EVENTS)
                    eoldidx = 0;
            }
        }
        e = &ebuffer[elastidx];
        e->event_source = source;
        e->event_idx = idx;
	e->first_stamp = e->last_stamp = (u32)ktime_get_real_seconds();
        e->same_count = 1;
        e->event_data = *evt;
        e->application = 0;
    }
    return e;
}