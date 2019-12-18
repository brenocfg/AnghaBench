#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {void* families; void* families_pattern; void* hosts; void* hosts_pattern; void* contexts; void* contexts_pattern; void* charts; void* charts_pattern; void* alarms; void* alarms_pattern; } ;
typedef  TYPE_1__ SILENCER ;

/* Variables and functions */
 char* HEALTH_ALARM_KEY ; 
 char* HEALTH_CHART_KEY ; 
 char* HEALTH_CONTEXT_KEY ; 
 char* HEALTH_FAMILIES_KEY ; 
 char* HEALTH_HOST_KEY ; 
 char* HEALTH_TEMPLATE_KEY ; 
 int /*<<< orphan*/  SIMPLE_PATTERN_EXACT ; 
 TYPE_1__* create_silencer () ; 
 int /*<<< orphan*/  error (char*) ; 
 void* simple_pattern_create (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ simple_uhash (char*) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 void* strdupz (char*) ; 
 scalar_t__ unlikely (int) ; 

SILENCER *health_silencers_addparam(SILENCER *silencer, char *key, char *value) {
    static uint32_t
            hash_alarm = 0,
            hash_template = 0,
            hash_chart = 0,
            hash_context = 0,
            hash_host = 0,
            hash_families = 0;

    if (unlikely(!hash_alarm)) {
        hash_alarm = simple_uhash(HEALTH_ALARM_KEY);
        hash_template = simple_uhash(HEALTH_TEMPLATE_KEY);
        hash_chart = simple_uhash(HEALTH_CHART_KEY);
        hash_context = simple_uhash(HEALTH_CONTEXT_KEY);
        hash_host = simple_uhash(HEALTH_HOST_KEY);
        hash_families = simple_uhash(HEALTH_FAMILIES_KEY);
    }

    uint32_t hash = simple_uhash(key);
    if (unlikely(silencer == NULL)) {
        if (
                (hash == hash_alarm && !strcasecmp(key, HEALTH_ALARM_KEY)) ||
                (hash == hash_template && !strcasecmp(key, HEALTH_TEMPLATE_KEY)) ||
                (hash == hash_chart && !strcasecmp(key, HEALTH_CHART_KEY)) ||
                (hash == hash_context && !strcasecmp(key, HEALTH_CONTEXT_KEY)) ||
                (hash == hash_host && !strcasecmp(key, HEALTH_HOST_KEY)) ||
                (hash == hash_families && !strcasecmp(key, HEALTH_FAMILIES_KEY))
                ) {
            silencer = create_silencer();
            if(!silencer) {
                error("Cannot add a new silencer to Netdata");
                return NULL;
            }
        }
    }

    if (hash == hash_alarm && !strcasecmp(key, HEALTH_ALARM_KEY)) {
        silencer->alarms = strdupz(value);
        silencer->alarms_pattern = simple_pattern_create(silencer->alarms, NULL, SIMPLE_PATTERN_EXACT);
    } else if (hash == hash_chart && !strcasecmp(key, HEALTH_CHART_KEY)) {
        silencer->charts = strdupz(value);
        silencer->charts_pattern = simple_pattern_create(silencer->charts, NULL, SIMPLE_PATTERN_EXACT);
    } else if (hash == hash_context && !strcasecmp(key, HEALTH_CONTEXT_KEY)) {
        silencer->contexts = strdupz(value);
        silencer->contexts_pattern = simple_pattern_create(silencer->contexts, NULL, SIMPLE_PATTERN_EXACT);
    } else if (hash == hash_host && !strcasecmp(key, HEALTH_HOST_KEY)) {
        silencer->hosts = strdupz(value);
        silencer->hosts_pattern = simple_pattern_create(silencer->hosts, NULL, SIMPLE_PATTERN_EXACT);
    } else if (hash == hash_families && !strcasecmp(key, HEALTH_FAMILIES_KEY)) {
        silencer->families = strdupz(value);
        silencer->families_pattern = simple_pattern_create(silencer->families, NULL, SIMPLE_PATTERN_EXACT);
    }

    return silencer;
}