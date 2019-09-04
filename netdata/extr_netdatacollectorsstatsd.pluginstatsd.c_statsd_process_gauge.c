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
struct TYPE_6__ {int value; } ;
struct TYPE_7__ {int reset; int /*<<< orphan*/  count; int /*<<< orphan*/  events; TYPE_1__ gauge; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ STATSD_METRIC ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_metric_useful_for_collection (TYPE_2__*) ; 
 int statsd_parse_float (char const*,double) ; 
 int statsd_parse_sampling_rate (char const*) ; 
 int /*<<< orphan*/  statsd_reset_metric (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 
 int value_is_zinit (char const*) ; 

__attribute__((used)) static inline void statsd_process_gauge(STATSD_METRIC *m, const char *value, const char *sampling) {
    if(!is_metric_useful_for_collection(m)) return;

    if(unlikely(!value || !*value)) {
        error("STATSD: metric '%s' of type gauge, with empty value is ignored.", m->name);
        return;
    }

    if(unlikely(m->reset)) {
        // no need to reset anything specific for gauges
        statsd_reset_metric(m);
    }

    if(unlikely(value_is_zinit(value))) {
        // magic loading of metric, without affecting anything
    }
    else {
        if (unlikely(*value == '+' || *value == '-'))
            m->gauge.value += statsd_parse_float(value, 1.0) / statsd_parse_sampling_rate(sampling);
        else
            m->gauge.value = statsd_parse_float(value, 1.0);

        m->events++;
        m->count++;
    }
}