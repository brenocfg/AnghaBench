#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* apps; } ;
struct TYPE_7__ {TYPE_1__* charts; struct TYPE_7__* next; } ;
struct TYPE_6__ {int /*<<< orphan*/  dimensions_linked_count; struct TYPE_6__* next; } ;
typedef  TYPE_1__ STATSD_APP_CHART ;
typedef  TYPE_2__ STATSD_APP ;

/* Variables and functions */
 TYPE_5__ statsd ; 
 int /*<<< orphan*/  statsd_update_app_chart (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void statsd_update_all_app_charts(void) {
    // debug(D_STATSD, "updating app charts");

    STATSD_APP *app;
    for(app = statsd.apps; app ;app = app->next) {
        // debug(D_STATSD, "updating charts for app '%s'", app->name);

        STATSD_APP_CHART *chart;
        for(chart = app->charts; chart ;chart = chart->next) {
            if(unlikely(chart->dimensions_linked_count)) {
                statsd_update_app_chart(app, chart);
            }
        }
    }

    // debug(D_STATSD, "completed update of app charts");
}