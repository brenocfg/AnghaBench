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
typedef  int STATSD_APP_CHART_DIM_VALUE_TYPE ;

/* Variables and functions */
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_AVERAGE 136 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_EVENTS 135 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_LAST 134 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_MAX 133 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_MEDIAN 132 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_MIN 131 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_PERCENTILE 130 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_STDDEV 129 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_SUM 128 

__attribute__((used)) static const char *valuetype2string(STATSD_APP_CHART_DIM_VALUE_TYPE type) {
    switch(type) {
        case STATSD_APP_CHART_DIM_VALUE_TYPE_EVENTS: return "events";
        case STATSD_APP_CHART_DIM_VALUE_TYPE_LAST: return "last";
        case STATSD_APP_CHART_DIM_VALUE_TYPE_MIN: return "min";
        case STATSD_APP_CHART_DIM_VALUE_TYPE_MAX: return "max";
        case STATSD_APP_CHART_DIM_VALUE_TYPE_SUM: return "sum";
        case STATSD_APP_CHART_DIM_VALUE_TYPE_AVERAGE: return "average";
        case STATSD_APP_CHART_DIM_VALUE_TYPE_MEDIAN: return "median";
        case STATSD_APP_CHART_DIM_VALUE_TYPE_STDDEV: return "stddev";
        case STATSD_APP_CHART_DIM_VALUE_TYPE_PERCENTILE: return "percentile";
    }

    return "unknown";
}