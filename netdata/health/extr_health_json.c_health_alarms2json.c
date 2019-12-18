#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ status; TYPE_3__* rrdset; struct TYPE_15__* next; } ;
struct TYPE_11__ {scalar_t__ next_log_id; } ;
struct TYPE_14__ {TYPE_5__* alarms; scalar_t__ health_enabled; TYPE_1__ health_log; int /*<<< orphan*/  hostname; } ;
struct TYPE_12__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_13__ {TYPE_2__ last_collected_time; } ;
typedef  TYPE_4__ RRDHOST ;
typedef  TYPE_5__ RRDCALC ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 scalar_t__ RRDCALC_STATUS_CRITICAL ; 
 scalar_t__ RRDCALC_STATUS_WARNING ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,char*,unsigned long) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  health_rrdcalc2json_nolock (TYPE_4__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ now_realtime_sec () ; 
 int /*<<< orphan*/  rrdhost_rdlock (TYPE_4__*) ; 
 int /*<<< orphan*/  rrdhost_unlock (TYPE_4__*) ; 
 scalar_t__ unlikely (int) ; 

void health_alarms2json(RRDHOST *host, BUFFER *wb, int all) {
    int i;

    rrdhost_rdlock(host);
    buffer_sprintf(wb, "{\n\t\"hostname\": \"%s\","
                    "\n\t\"latest_alarm_log_unique_id\": %u,"
                    "\n\t\"status\": %s,"
                    "\n\t\"now\": %lu,"
                    "\n\t\"alarms\": {\n",
            host->hostname,
            (host->health_log.next_log_id > 0)?(host->health_log.next_log_id - 1):0,
            host->health_enabled?"true":"false",
            (unsigned long)now_realtime_sec());

    RRDCALC *rc;
    for(i = 0, rc = host->alarms; rc ; rc = rc->next) {
        if(unlikely(!rc->rrdset || !rc->rrdset->last_collected_time.tv_sec))
            continue;

        if(likely(!all && !(rc->status == RRDCALC_STATUS_WARNING || rc->status == RRDCALC_STATUS_CRITICAL)))
            continue;

        if(likely(i)) buffer_strcat(wb, ",\n");
        health_rrdcalc2json_nolock(host, wb, rc);
        i++;
    }

//    buffer_strcat(wb, "\n\t},\n\t\"templates\": {");
//    RRDCALCTEMPLATE *rt;
//    for(rt = host->templates; rt ; rt = rt->next)
//        health_rrdcalctemplate2json_nolock(wb, rt);

    buffer_strcat(wb, "\n\t}\n}\n");
    rrdhost_unlock(host);
}