#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ STATSD_METRIC ;
typedef  int /*<<< orphan*/  RRD_ALGORITHM ;

/* Variables and functions */
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
#define  STATSD_METRIC_TYPE_COUNTER 133 
#define  STATSD_METRIC_TYPE_GAUGE 132 
#define  STATSD_METRIC_TYPE_HISTOGRAM 131 
#define  STATSD_METRIC_TYPE_METER 130 
#define  STATSD_METRIC_TYPE_SET 129 
#define  STATSD_METRIC_TYPE_TIMER 128 

__attribute__((used)) static inline RRD_ALGORITHM statsd_algorithm_for_metric(STATSD_METRIC *m) {
    switch(m->type) {
        default:
        case STATSD_METRIC_TYPE_GAUGE:
        case STATSD_METRIC_TYPE_SET:
        case STATSD_METRIC_TYPE_TIMER:
        case STATSD_METRIC_TYPE_HISTOGRAM:
            return RRD_ALGORITHM_ABSOLUTE;

        case STATSD_METRIC_TYPE_METER:
        case STATSD_METRIC_TYPE_COUNTER:
            return RRD_ALGORITHM_INCREMENTAL;
    }
}