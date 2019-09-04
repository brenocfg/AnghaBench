#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int decimal_detail; int /*<<< orphan*/  update_every; } ;
struct TYPE_6__ {int options; scalar_t__ st; int /*<<< orphan*/  events; void* rd_count; int /*<<< orphan*/  last; void* rd_value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ STATSD_METRIC ;

/* Variables and functions */
 int /*<<< orphan*/  D_STATSD ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_STATSD_PRIVATE ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  RRD_ID_LENGTH_MAX ; 
 int STATSD_METRIC_OPTION_CHART_DIMENSION_COUNT ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* rrddim_add (scalar_t__,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (scalar_t__) ; 
 int /*<<< orphan*/  rrdset_next (scalar_t__) ; 
 int /*<<< orphan*/  snprintfz (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__ statsd ; 
 int /*<<< orphan*/  statsd_get_metric_type_and_id (TYPE_1__*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ statsd_private_rrdset_create (TYPE_1__*,char*,char*,int /*<<< orphan*/ *,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void statsd_private_chart_gauge(STATSD_METRIC *m) {
    debug(D_STATSD, "updating private chart for gauge metric '%s'", m->name);

    if(unlikely(!m->st)) {
        char type[RRD_ID_LENGTH_MAX + 1], id[RRD_ID_LENGTH_MAX + 1];
        statsd_get_metric_type_and_id(m, type, id, "gauge", RRD_ID_LENGTH_MAX);

        char context[RRD_ID_LENGTH_MAX + 1];
        snprintfz(context, RRD_ID_LENGTH_MAX, "statsd_gauge.%s", m->name);

        char title[RRD_ID_LENGTH_MAX + 1];
        snprintfz(title, RRD_ID_LENGTH_MAX, "statsd private chart for gauge %s", m->name);

        m->st = statsd_private_rrdset_create(
                m
                , type
                , id
                , NULL          // name
                , "gauges"      // family (submenu)
                , context       // context
                , title         // title
                , "value"       // units
                , NETDATA_CHART_PRIO_STATSD_PRIVATE
                , statsd.update_every
                , RRDSET_TYPE_LINE
        );

        m->rd_value = rrddim_add(m->st, "gauge",  NULL, 1, statsd.decimal_detail, RRD_ALGORITHM_ABSOLUTE);

        if(m->options & STATSD_METRIC_OPTION_CHART_DIMENSION_COUNT)
            m->rd_count = rrddim_add(m->st, "events", NULL, 1, 1,    RRD_ALGORITHM_INCREMENTAL);
    }
    else rrdset_next(m->st);

    rrddim_set_by_pointer(m->st, m->rd_value, m->last);

    if(m->rd_count)
        rrddim_set_by_pointer(m->st, m->rd_count, m->events);

    rrdset_done(m->st);
}