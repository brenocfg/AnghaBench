#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ stype; TYPE_1__* silencers; scalar_t__ all_alarms; } ;
struct TYPE_3__ {int /*<<< orphan*/  families; int /*<<< orphan*/  hosts; int /*<<< orphan*/  contexts; int /*<<< orphan*/  charts; int /*<<< orphan*/  alarms; struct TYPE_3__* next; } ;
typedef  TYPE_1__ SILENCER ;
typedef  int /*<<< orphan*/  BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  HEALTH_ALARM_KEY ; 
 int /*<<< orphan*/  HEALTH_CHART_KEY ; 
 int /*<<< orphan*/  HEALTH_CONTEXT_KEY ; 
 int /*<<< orphan*/  HEALTH_FAMILIES_KEY ; 
 int /*<<< orphan*/  HEALTH_HOST_KEY ; 
 scalar_t__ STYPE_DISABLE_ALARMS ; 
 scalar_t__ STYPE_NONE ; 
 int /*<<< orphan*/  buffer_sprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  buffer_strcat (int /*<<< orphan*/ *,char*) ; 
 int health_silencers2json_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 TYPE_2__* silencers ; 

void health_silencers2json(BUFFER *wb) {
    buffer_sprintf(wb, "{\n\t\"all\": %s,"
                       "\n\t\"type\": \"%s\","
                       "\n\t\"silencers\": [",
                   (silencers->all_alarms)?"true":"false",
                   (silencers->stype == STYPE_NONE)?"None":((silencers->stype == STYPE_DISABLE_ALARMS)?"DISABLE":"SILENCE"));

    SILENCER *silencer;
    int i = 0, j = 0;
    for(silencer = silencers->silencers; silencer ; silencer = silencer->next) {
        if(likely(i)) buffer_strcat(wb, ",");
        buffer_strcat(wb, "\n\t\t{");
        j=health_silencers2json_entry(wb, HEALTH_ALARM_KEY, silencer->alarms, j);
        j=health_silencers2json_entry(wb, HEALTH_CHART_KEY, silencer->charts, j);
        j=health_silencers2json_entry(wb, HEALTH_CONTEXT_KEY, silencer->contexts, j);
        j=health_silencers2json_entry(wb, HEALTH_HOST_KEY, silencer->hosts, j);
        health_silencers2json_entry(wb, HEALTH_FAMILIES_KEY, silencer->families, j);
        j=0;
        buffer_strcat(wb, "\n\t\t}");
        i++;
    }
    if(likely(i)) buffer_strcat(wb, "\n\t");
    buffer_strcat(wb, "]\n}\n");
}