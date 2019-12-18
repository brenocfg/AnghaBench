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
typedef  scalar_t__ collected_number ;
struct TYPE_8__ {int decimal_detail; } ;
struct TYPE_6__ {int value; } ;
struct TYPE_7__ {int reset; int options; TYPE_1__ gauge; scalar_t__ last; scalar_t__ count; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ STATSD_METRIC ;

/* Variables and functions */
 int /*<<< orphan*/  D_STATSD ; 
 int STATSD_METRIC_OPTION_PRIVATE_CHART_ENABLED ; 
 int STATSD_METRIC_OPTION_SHOW_GAPS_WHEN_NOT_COLLECTED ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_5__ statsd ; 
 int /*<<< orphan*/  statsd_private_chart_gauge (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void statsd_flush_gauge(STATSD_METRIC *m) {
    debug(D_STATSD, "flushing gauge metric '%s'", m->name);

    int updated = 0;
    if(unlikely(!m->reset && m->count)) {
        m->last = (collected_number) (m->gauge.value * statsd.decimal_detail);

        m->reset = 1;
        updated = 1;
    }

    if(unlikely(m->options & STATSD_METRIC_OPTION_PRIVATE_CHART_ENABLED && (updated || !(m->options & STATSD_METRIC_OPTION_SHOW_GAPS_WHEN_NOT_COLLECTED))))
        statsd_private_chart_gauge(m);
}