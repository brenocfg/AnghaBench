#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int STATSD_METRIC_TYPE ;

/* Variables and functions */
#define  STATSD_METRIC_TYPE_COUNTER 133 
#define  STATSD_METRIC_TYPE_GAUGE 132 
#define  STATSD_METRIC_TYPE_HISTOGRAM 131 
#define  STATSD_METRIC_TYPE_METER 130 
#define  STATSD_METRIC_TYPE_SET 129 
#define  STATSD_METRIC_TYPE_TIMER 128 

const char *statsd_metric_type_string(STATSD_METRIC_TYPE type) {
    switch(type) {
        case STATSD_METRIC_TYPE_COUNTER: return "counter";
        case STATSD_METRIC_TYPE_GAUGE: return "gauge";
        case STATSD_METRIC_TYPE_HISTOGRAM: return "histogram";
        case STATSD_METRIC_TYPE_METER: return "meter";
        case STATSD_METRIC_TYPE_SET: return "set";
        case STATSD_METRIC_TYPE_TIMER: return "timer";
        default: return "unknown";
    }
}