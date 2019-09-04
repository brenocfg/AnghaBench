#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  st; TYPE_1__* dimensions; } ;
struct TYPE_7__ {scalar_t__ metric_hash; char* metric; scalar_t__ value_type; TYPE_3__* rd; int /*<<< orphan*/  flags; int /*<<< orphan*/  algorithm; int /*<<< orphan*/  divisor; int /*<<< orphan*/  multiplier; int /*<<< orphan*/  name; struct TYPE_7__* next; } ;
typedef  TYPE_1__ STATSD_APP_CHART_DIM ;
typedef  TYPE_2__ STATSD_APP_CHART ;
typedef  int /*<<< orphan*/  STATSD_APP ;
typedef  TYPE_3__ RRDDIM ;

/* Variables and functions */
 int /*<<< orphan*/  RRDDIM_FLAG_NONE ; 
 void* rrddim_add (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintfz (char*,size_t,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  valuetype2string (scalar_t__) ; 

__attribute__((used)) static inline RRDDIM *statsd_add_dim_to_app_chart(STATSD_APP *app, STATSD_APP_CHART *chart, STATSD_APP_CHART_DIM *dim) {
    (void)app;

    // allow the same statsd metric to be added multiple times to the same chart

    STATSD_APP_CHART_DIM *tdim;
    size_t count_same_metric = 0, count_same_metric_value_type = 0;
    size_t pos_same_metric_value_type = 0;

    for (tdim = chart->dimensions; tdim && tdim->next; tdim = tdim->next) {
        if (dim->metric_hash == tdim->metric_hash && !strcmp(dim->metric, tdim->metric)) {
            count_same_metric++;

            if(dim->value_type == tdim->value_type) {
                count_same_metric_value_type++;
                if (tdim == dim)
                    pos_same_metric_value_type = count_same_metric_value_type;
            }
        }
    }

    if(count_same_metric > 1) {
        // the same metric is found multiple times

        size_t len = strlen(dim->metric) + 100;
        char metric[ len + 1 ];

        if(count_same_metric_value_type > 1) {
            // the same metric, with the same value type, is added multiple times
            snprintfz(metric, len, "%s_%s%zu", dim->metric, valuetype2string(dim->value_type), pos_same_metric_value_type);
        }
        else {
            // the same metric, with different value type is added
            snprintfz(metric, len, "%s_%s", dim->metric, valuetype2string(dim->value_type));
        }

        dim->rd = rrddim_add(chart->st, metric, dim->name, dim->multiplier, dim->divisor, dim->algorithm);
        if(dim->flags != RRDDIM_FLAG_NONE) dim->rd->flags |= dim->flags;
        return dim->rd;
    }

    dim->rd = rrddim_add(chart->st, dim->metric, dim->name, dim->multiplier, dim->divisor, dim->algorithm);
    if(dim->flags != RRDDIM_FLAG_NONE) dim->rd->flags |= dim->flags;
    return dim->rd;
}