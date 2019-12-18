#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  unknown_types; int /*<<< orphan*/  timers; int /*<<< orphan*/  sets; int /*<<< orphan*/  histograms; int /*<<< orphan*/  meters; int /*<<< orphan*/  counters; int /*<<< orphan*/  gauges; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STATSD ; 
 int /*<<< orphan*/  STATSD_METRIC_TYPE_COUNTER ; 
 int /*<<< orphan*/  STATSD_METRIC_TYPE_GAUGE ; 
 int /*<<< orphan*/  STATSD_METRIC_TYPE_HISTOGRAM ; 
 int /*<<< orphan*/  STATSD_METRIC_TYPE_METER ; 
 int /*<<< orphan*/  STATSD_METRIC_TYPE_SET ; 
 int /*<<< orphan*/  STATSD_METRIC_TYPE_TIMER ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  error (char*,char const*,char const*,char const*) ; 
 TYPE_1__ statsd ; 
 int /*<<< orphan*/  statsd_find_or_add_metric (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  statsd_process_counter (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  statsd_process_gauge (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  statsd_process_histogram (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  statsd_process_meter (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  statsd_process_set (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  statsd_process_timer (int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void statsd_process_metric(const char *name, const char *value, const char *type, const char *sampling, const char *tags) {
    (void)tags;

    debug(D_STATSD, "STATSD: raw metric '%s', value '%s', type '%s', sampling '%s', tags '%s'", name?name:"(null)", value?value:"(null)", type?type:"(null)", sampling?sampling:"(null)", tags?tags:"(null)");

    if(unlikely(!name || !*name)) return;
    if(unlikely(!type || !*type)) type = "m";

    char t0 = type[0], t1 = type[1];

    if(unlikely(t0 == 'g' && t1 == '\0')) {
        statsd_process_gauge(
                statsd_find_or_add_metric(&statsd.gauges, name, STATSD_METRIC_TYPE_GAUGE),
                value, sampling);
    }
    else if(unlikely((t0 == 'c' || t0 == 'C') && t1 == '\0')) {
        // etsy/statsd uses 'c'
        // brubeck     uses 'C'
        statsd_process_counter(
                statsd_find_or_add_metric(&statsd.counters, name, STATSD_METRIC_TYPE_COUNTER),
                value, sampling);
    }
    else if(unlikely(t0 == 'm' && t1 == '\0')) {
        statsd_process_meter(
                statsd_find_or_add_metric(&statsd.meters, name, STATSD_METRIC_TYPE_METER),
                value, sampling);
    }
    else if(unlikely(t0 == 'h' && t1 == '\0')) {
        statsd_process_histogram(
                statsd_find_or_add_metric(&statsd.histograms, name, STATSD_METRIC_TYPE_HISTOGRAM),
                value, sampling);
    }
    else if(unlikely(t0 == 's' && t1 == '\0')) {
        statsd_process_set(
                statsd_find_or_add_metric(&statsd.sets, name, STATSD_METRIC_TYPE_SET),
                value);
    }
    else if(unlikely(t0 == 'm' && t1 == 's' && type[2] == '\0')) {
        statsd_process_timer(
                statsd_find_or_add_metric(&statsd.timers, name, STATSD_METRIC_TYPE_TIMER),
                value, sampling);
    }
    else {
        statsd.unknown_types++;
        error("STATSD: metric '%s' with value '%s' is sent with unknown metric type '%s'", name, value?value:"", type);
    }
}