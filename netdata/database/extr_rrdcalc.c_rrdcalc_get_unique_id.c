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
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {scalar_t__ hash_name; scalar_t__ hash_chart; scalar_t__ alarm_event_id; scalar_t__ alarm_id; int /*<<< orphan*/  chart; int /*<<< orphan*/  name; struct TYPE_7__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  next_alarm_id; TYPE_3__* alarms; } ;
struct TYPE_6__ {TYPE_1__ health_log; } ;
typedef  TYPE_2__ RRDHOST ;
typedef  TYPE_3__ ALARM_ENTRY ;

/* Variables and functions */
 scalar_t__ simple_hash (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

inline uint32_t rrdcalc_get_unique_id(RRDHOST *host, const char *chart, const char *name, uint32_t *next_event_id) {
    if(chart && name) {
        uint32_t hash_chart = simple_hash(chart);
        uint32_t hash_name = simple_hash(name);

        // re-use old IDs, by looking them up in the alarm log
        ALARM_ENTRY *ae;
        for(ae = host->health_log.alarms; ae ;ae = ae->next) {
            if(unlikely(ae->hash_name == hash_name && ae->hash_chart == hash_chart && !strcmp(name, ae->name) && !strcmp(chart, ae->chart))) {
                if(next_event_id) *next_event_id = ae->alarm_event_id + 1;
                return ae->alarm_id;
            }
        }
    }

    return host->health_log.next_alarm_id++;
}