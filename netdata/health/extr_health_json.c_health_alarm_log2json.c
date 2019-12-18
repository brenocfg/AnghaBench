#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {scalar_t__ unique_id; struct TYPE_9__* next; } ;
struct TYPE_7__ {unsigned int max; int /*<<< orphan*/  alarm_log_rwlock; TYPE_3__* alarms; } ;
struct TYPE_8__ {TYPE_1__ health_log; } ;
typedef  TYPE_2__ RRDHOST ;
typedef  int /*<<< orphan*/  BUFFER ;
typedef  TYPE_3__ ALARM_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  health_alarm_entry2json_nolock (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ likely (unsigned int) ; 
 int /*<<< orphan*/  netdata_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdata_rwlock_unlock (int /*<<< orphan*/ *) ; 

void health_alarm_log2json(RRDHOST *host, BUFFER *wb, uint32_t after) {
    netdata_rwlock_rdlock(&host->health_log.alarm_log_rwlock);

    buffer_strcat(wb, "[");

    unsigned int max = host->health_log.max;
    unsigned int count = 0;
    ALARM_ENTRY *ae;
    for(ae = host->health_log.alarms; ae && count < max ; count++, ae = ae->next) {
        if(ae->unique_id > after) {
            if(likely(count)) buffer_strcat(wb, ",");
            health_alarm_entry2json_nolock(wb, ae, host);
        }
    }

    buffer_strcat(wb, "\n]\n");

    netdata_rwlock_unlock(&host->health_log.alarm_log_rwlock);
}