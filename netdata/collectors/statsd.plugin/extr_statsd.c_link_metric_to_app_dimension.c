#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  decimal_detail; } ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;
struct TYPE_17__ {char* id; int /*<<< orphan*/  dimensions_linked_count; scalar_t__ st; } ;
struct TYPE_16__ {int value_type; int /*<<< orphan*/  algorithm; int /*<<< orphan*/  name; int /*<<< orphan*/  divisor; scalar_t__ rd; int /*<<< orphan*/  multiplier; int /*<<< orphan*/ * value_ptr; } ;
struct TYPE_14__ {TYPE_1__* ext; } ;
struct TYPE_15__ {scalar_t__ type; int /*<<< orphan*/  name; int /*<<< orphan*/  options; int /*<<< orphan*/  last; TYPE_2__ histogram; int /*<<< orphan*/  events; } ;
struct TYPE_13__ {int /*<<< orphan*/  last_stddev; int /*<<< orphan*/  last_percentile; int /*<<< orphan*/  last_median; int /*<<< orphan*/  last_max; int /*<<< orphan*/  last_min; int /*<<< orphan*/  last_sum; } ;
typedef  TYPE_3__ STATSD_METRIC ;
typedef  TYPE_4__ STATSD_APP_CHART_DIM ;
typedef  TYPE_5__ STATSD_APP_CHART ;
typedef  TYPE_6__ STATSD_APP ;

/* Variables and functions */
 int /*<<< orphan*/  D_STATSD ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_AVERAGE 136 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_EVENTS 135 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_LAST 134 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_MAX 133 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_MEDIAN 132 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_MIN 131 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_PERCENTILE 130 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_STDDEV 129 
#define  STATSD_APP_CHART_DIM_VALUE_TYPE_SUM 128 
 int /*<<< orphan*/  STATSD_METRIC_OPTION_USED_IN_APPS ; 
 scalar_t__ STATSD_METRIC_TYPE_GAUGE ; 
 scalar_t__ STATSD_METRIC_TYPE_HISTOGRAM ; 
 scalar_t__ STATSD_METRIC_TYPE_TIMER ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrd_algorithm_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_algorithm (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_divisor (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_multiplier (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_8__ statsd ; 
 int /*<<< orphan*/  statsd_algorithm_for_metric (TYPE_3__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void link_metric_to_app_dimension(STATSD_APP *app, STATSD_METRIC *m, STATSD_APP_CHART *chart, STATSD_APP_CHART_DIM *dim) {
    if(dim->value_type == STATSD_APP_CHART_DIM_VALUE_TYPE_EVENTS) {
        dim->value_ptr = &m->events;
        dim->algorithm = RRD_ALGORITHM_INCREMENTAL;
    }
    else if(m->type == STATSD_METRIC_TYPE_HISTOGRAM || m->type == STATSD_METRIC_TYPE_TIMER) {
        dim->algorithm = RRD_ALGORITHM_ABSOLUTE;
        dim->divisor *= statsd.decimal_detail;

        switch(dim->value_type) {
            case STATSD_APP_CHART_DIM_VALUE_TYPE_EVENTS:
                // will never match - added to avoid warning
                break;

            case STATSD_APP_CHART_DIM_VALUE_TYPE_LAST:
            case STATSD_APP_CHART_DIM_VALUE_TYPE_AVERAGE:
                dim->value_ptr = &m->last;
                break;

            case STATSD_APP_CHART_DIM_VALUE_TYPE_SUM:
                dim->value_ptr = &m->histogram.ext->last_sum;
                break;

            case STATSD_APP_CHART_DIM_VALUE_TYPE_MIN:
                dim->value_ptr = &m->histogram.ext->last_min;
                break;

            case STATSD_APP_CHART_DIM_VALUE_TYPE_MAX:
                dim->value_ptr = &m->histogram.ext->last_max;
                break;

            case STATSD_APP_CHART_DIM_VALUE_TYPE_MEDIAN:
                dim->value_ptr = &m->histogram.ext->last_median;
                break;

            case STATSD_APP_CHART_DIM_VALUE_TYPE_PERCENTILE:
                dim->value_ptr = &m->histogram.ext->last_percentile;
                break;

            case STATSD_APP_CHART_DIM_VALUE_TYPE_STDDEV:
                dim->value_ptr = &m->histogram.ext->last_stddev;
                break;
        }
    }
    else {
        if (dim->value_type != STATSD_APP_CHART_DIM_VALUE_TYPE_LAST)
            error("STATSD: unsupported value type for dimension '%s' of chart '%s' of app '%s' on metric '%s'", dim->name, chart->id, app->name, m->name);

        dim->value_ptr = &m->last;
        dim->algorithm = statsd_algorithm_for_metric(m);

        if(m->type == STATSD_METRIC_TYPE_GAUGE)
            dim->divisor *= statsd.decimal_detail;
    }

    if(unlikely(chart->st && dim->rd)) {
        rrddim_set_algorithm(chart->st, dim->rd, dim->algorithm);
        rrddim_set_multiplier(chart->st, dim->rd, dim->multiplier);
        rrddim_set_divisor(chart->st, dim->rd, dim->divisor);
    }

    chart->dimensions_linked_count++;
    m->options |= STATSD_METRIC_OPTION_USED_IN_APPS;
    debug(D_STATSD, "metric '%s' of type %u linked with app '%s', chart '%s', dimension '%s', algorithm '%s'", m->name, m->type, app->name, chart->id, dim->name, rrd_algorithm_name(dim->algorithm));
}