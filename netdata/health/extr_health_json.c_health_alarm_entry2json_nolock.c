#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; char* units; char* info; int /*<<< orphan*/  old_value; int /*<<< orphan*/  new_value; scalar_t__ last_repeat; int /*<<< orphan*/  old_value_string; int /*<<< orphan*/  new_value_string; int /*<<< orphan*/  updates_id; int /*<<< orphan*/  updated_by_id; scalar_t__ delay_up_to_timestamp; int /*<<< orphan*/  delay; int /*<<< orphan*/  old_status; int /*<<< orphan*/  new_status; scalar_t__ non_clear_duration; scalar_t__ duration; scalar_t__ when; int /*<<< orphan*/  source; int /*<<< orphan*/  exec_code; scalar_t__ recipient; scalar_t__ exec; scalar_t__ exec_run_timestamp; int /*<<< orphan*/  family; int /*<<< orphan*/  chart; int /*<<< orphan*/  name; int /*<<< orphan*/  alarm_event_id; int /*<<< orphan*/  alarm_id; int /*<<< orphan*/  unique_id; } ;
struct TYPE_5__ {scalar_t__ health_default_recipient; scalar_t__ health_default_exec; int /*<<< orphan*/  hostname; } ;
typedef  TYPE_1__ RRDHOST ;
typedef  int /*<<< orphan*/  BUFFER ;
typedef  TYPE_2__ ALARM_ENTRY ;

/* Variables and functions */
 int HEALTH_ENTRY_FLAG_EXEC_FAILED ; 
 int HEALTH_ENTRY_FLAG_NO_CLEAR_NOTIFICATION ; 
 int HEALTH_ENTRY_FLAG_PROCESSED ; 
 int HEALTH_ENTRY_FLAG_SILENCED ; 
 int HEALTH_ENTRY_FLAG_UPDATED ; 
 int /*<<< orphan*/  buffer_rrd_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,unsigned long,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,char*) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  health_string2json (int /*<<< orphan*/ *,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  rrdcalc_status2string (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void health_alarm_entry2json_nolock(BUFFER *wb, ALARM_ENTRY *ae, RRDHOST *host) {
    buffer_sprintf(wb,
            "\n\t{\n"
                    "\t\t\"hostname\": \"%s\",\n"
                    "\t\t\"unique_id\": %u,\n"
                    "\t\t\"alarm_id\": %u,\n"
                    "\t\t\"alarm_event_id\": %u,\n"
                    "\t\t\"name\": \"%s\",\n"
                    "\t\t\"chart\": \"%s\",\n"
                    "\t\t\"family\": \"%s\",\n"
                    "\t\t\"processed\": %s,\n"
                    "\t\t\"updated\": %s,\n"
                    "\t\t\"exec_run\": %lu,\n"
                    "\t\t\"exec_failed\": %s,\n"
                    "\t\t\"exec\": \"%s\",\n"
                    "\t\t\"recipient\": \"%s\",\n"
                    "\t\t\"exec_code\": %d,\n"
                    "\t\t\"source\": \"%s\",\n"
                    "\t\t\"units\": \"%s\",\n"
                    "\t\t\"when\": %lu,\n"
                    "\t\t\"duration\": %lu,\n"
                    "\t\t\"non_clear_duration\": %lu,\n"
                    "\t\t\"status\": \"%s\",\n"
                    "\t\t\"old_status\": \"%s\",\n"
                    "\t\t\"delay\": %d,\n"
                    "\t\t\"delay_up_to_timestamp\": %lu,\n"
                    "\t\t\"updated_by_id\": %u,\n"
                    "\t\t\"updates_id\": %u,\n"
                    "\t\t\"value_string\": \"%s\",\n"
                    "\t\t\"old_value_string\": \"%s\",\n"
                    "\t\t\"last_repeat\": \"%lu\",\n"
                    "\t\t\"silenced\": \"%s\",\n"
                   , host->hostname
                   , ae->unique_id
                   , ae->alarm_id
                   , ae->alarm_event_id
                   , ae->name
                   , ae->chart
                   , ae->family
                   , (ae->flags & HEALTH_ENTRY_FLAG_PROCESSED)?"true":"false"
                   , (ae->flags & HEALTH_ENTRY_FLAG_UPDATED)?"true":"false"
                   , (unsigned long)ae->exec_run_timestamp
                   , (ae->flags & HEALTH_ENTRY_FLAG_EXEC_FAILED)?"true":"false"
                   , ae->exec?ae->exec:host->health_default_exec
                   , ae->recipient?ae->recipient:host->health_default_recipient
                   , ae->exec_code
                   , ae->source
                   , ae->units?ae->units:""
                   , (unsigned long)ae->when
                   , (unsigned long)ae->duration
                   , (unsigned long)ae->non_clear_duration
                   , rrdcalc_status2string(ae->new_status)
                   , rrdcalc_status2string(ae->old_status)
                   , ae->delay
                   , (unsigned long)ae->delay_up_to_timestamp
                   , ae->updated_by_id
                   , ae->updates_id
                   , ae->new_value_string
                   , ae->old_value_string
                   , (unsigned long)ae->last_repeat
                   , (ae->flags & HEALTH_ENTRY_FLAG_SILENCED)?"true":"false"
    );

    health_string2json(wb, "\t\t", "info", ae->info?ae->info:"", ",\n");

    if(unlikely(ae->flags & HEALTH_ENTRY_FLAG_NO_CLEAR_NOTIFICATION)) {
        buffer_strcat(wb, "\t\t\"no_clear_notification\": true,\n");
    }

    buffer_strcat(wb, "\t\t\"value\":");
    buffer_rrd_value(wb, ae->new_value);
    buffer_strcat(wb, ",\n");

    buffer_strcat(wb, "\t\t\"old_value\":");
    buffer_rrd_value(wb, ae->old_value);
    buffer_strcat(wb, "\n");

    buffer_strcat(wb, "\t}");
}