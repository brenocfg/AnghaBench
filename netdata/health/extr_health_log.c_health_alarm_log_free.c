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
struct TYPE_9__ {struct TYPE_9__* next; } ;
struct TYPE_7__ {int /*<<< orphan*/  alarm_log_rwlock; TYPE_3__* alarms; } ;
struct TYPE_8__ {TYPE_1__ health_log; } ;
typedef  TYPE_2__ RRDHOST ;
typedef  TYPE_3__ ALARM_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  health_alarm_log_free_one_nochecks_nounlink (TYPE_3__*) ; 
 int /*<<< orphan*/  netdata_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdata_rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdhost_check_wrlock (TYPE_2__*) ; 

inline void health_alarm_log_free(RRDHOST *host) {
    rrdhost_check_wrlock(host);

    netdata_rwlock_wrlock(&host->health_log.alarm_log_rwlock);

    ALARM_ENTRY *ae;
    while((ae = host->health_log.alarms)) {
        host->health_log.alarms = ae->next;
        health_alarm_log_free_one_nochecks_nounlink(ae);
    }

    netdata_rwlock_unlock(&host->health_log.alarm_log_rwlock);
}