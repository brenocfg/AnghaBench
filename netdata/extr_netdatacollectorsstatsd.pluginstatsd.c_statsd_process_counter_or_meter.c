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
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int /*<<< orphan*/  count; int /*<<< orphan*/  events; TYPE_1__ counter; int /*<<< orphan*/  reset; } ;
typedef  TYPE_2__ STATSD_METRIC ;
typedef  int LONG_DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  is_metric_useful_for_collection (TYPE_2__*) ; 
 scalar_t__ llrintl (int) ; 
 scalar_t__ statsd_parse_int (char const*,int) ; 
 int statsd_parse_sampling_rate (char const*) ; 
 int /*<<< orphan*/  statsd_reset_metric (TYPE_2__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_is_zinit (char const*) ; 

__attribute__((used)) static inline void statsd_process_counter_or_meter(STATSD_METRIC *m, const char *value, const char *sampling) {
    if(!is_metric_useful_for_collection(m)) return;

    // we accept empty values for counters

    if(unlikely(m->reset)) statsd_reset_metric(m);

    if(unlikely(value_is_zinit(value))) {
        // magic loading of metric, without affecting anything
    }
    else {
        m->counter.value += llrintl((LONG_DOUBLE) statsd_parse_int(value, 1) / statsd_parse_sampling_rate(sampling));

        m->events++;
        m->count++;
    }
}