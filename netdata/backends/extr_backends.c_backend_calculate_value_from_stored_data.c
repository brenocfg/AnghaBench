#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct rrddim_query_handle {int dummy; } ;
typedef  int /*<<< orphan*/  storage_number ;
typedef  int calculated_number ;
struct TYPE_15__ {int /*<<< orphan*/  id; TYPE_2__* state; } ;
struct TYPE_14__ {int /*<<< orphan*/  hostname; } ;
struct TYPE_13__ {int update_every; int /*<<< orphan*/  id; TYPE_4__* rrdhost; } ;
struct TYPE_11__ {int (* oldest_time ) (TYPE_5__*) ;int (* latest_time ) (TYPE_5__*) ;int /*<<< orphan*/  (* finalize ) (struct rrddim_query_handle*) ;int /*<<< orphan*/  (* next_metric ) (struct rrddim_query_handle*,int*) ;int /*<<< orphan*/  (* is_finished ) (struct rrddim_query_handle*) ;int /*<<< orphan*/  (* init ) (TYPE_5__*,struct rrddim_query_handle*,int,int) ;} ;
struct TYPE_12__ {TYPE_1__ query_ops; } ;
typedef  TYPE_3__ RRDSET ;
typedef  TYPE_4__ RRDHOST ;
typedef  TYPE_5__ RRDDIM ;
typedef  int /*<<< orphan*/  BACKEND_OPTIONS ;

/* Variables and functions */
 scalar_t__ BACKEND_OPTIONS_DATA_SOURCE (int /*<<< orphan*/ ) ; 
 scalar_t__ BACKEND_SOURCE_DATA_SUM ; 
 int /*<<< orphan*/  D_BACKEND ; 
 int NAN ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long,...) ; 
 int /*<<< orphan*/  does_storage_number_exist (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_5__*) ; 
 int stub2 (TYPE_5__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,struct rrddim_query_handle*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct rrddim_query_handle*) ; 
 int /*<<< orphan*/  stub5 (struct rrddim_query_handle*,int*) ; 
 int /*<<< orphan*/  stub6 (struct rrddim_query_handle*) ; 
 scalar_t__ unlikely (int) ; 
 int unpack_storage_number (int /*<<< orphan*/ ) ; 

calculated_number backend_calculate_value_from_stored_data(
          RRDSET *st                // the chart
        , RRDDIM *rd                // the dimension
        , time_t after              // the start timestamp
        , time_t before             // the end timestamp
        , BACKEND_OPTIONS backend_options // BACKEND_SOURCE_* bitmap
        , time_t *first_timestamp   // the first point of the database used in this response
        , time_t *last_timestamp    // the timestamp that should be reported to backend
) {
    RRDHOST *host = st->rrdhost;
    (void)host;

    // find the edges of the rrd database for this chart
    time_t first_t = rd->state->query_ops.oldest_time(rd);
    time_t last_t  = rd->state->query_ops.latest_time(rd);
    time_t update_every = st->update_every;
    struct rrddim_query_handle handle;
    storage_number n;

    // step back a little, to make sure we have complete data collection
    // for all metrics
    after  -= update_every * 2;
    before -= update_every * 2;

    // align the time-frame
    after  = after  - (after  % update_every);
    before = before - (before % update_every);

    // for before, loose another iteration
    // the latest point will be reported the next time
    before -= update_every;

    if(unlikely(after > before))
        // this can happen when update_every > before - after
        after = before;

    if(unlikely(after < first_t))
        after = first_t;

    if(unlikely(before > last_t))
        before = last_t;

    if(unlikely(before < first_t || after > last_t)) {
        // the chart has not been updated in the wanted timeframe
        debug(D_BACKEND, "BACKEND: %s.%s.%s: aligned timeframe %lu to %lu is outside the chart's database range %lu to %lu",
              host->hostname, st->id, rd->id,
              (unsigned long)after, (unsigned long)before,
              (unsigned long)first_t, (unsigned long)last_t
        );
        return NAN;
    }

    *first_timestamp = after;
    *last_timestamp = before;

    size_t counter = 0;
    calculated_number sum = 0;

/*
    long    start_at_slot = rrdset_time2slot(st, before),
            stop_at_slot  = rrdset_time2slot(st, after),
            slot, stop_now = 0;

    for(slot = start_at_slot; !stop_now ; slot--) {

        if(unlikely(slot < 0)) slot = st->entries - 1;
        if(unlikely(slot == stop_at_slot)) stop_now = 1;

        storage_number n = rd->values[slot];

        if(unlikely(!does_storage_number_exist(n))) {
            // not collected
            continue;
        }

        calculated_number value = unpack_storage_number(n);
        sum += value;

        counter++;
    }
*/
    for(rd->state->query_ops.init(rd, &handle, after, before) ; !rd->state->query_ops.is_finished(&handle) ; ) {
        time_t curr_t;
        n = rd->state->query_ops.next_metric(&handle, &curr_t);

        if(unlikely(!does_storage_number_exist(n))) {
            // not collected
            continue;
        }

        calculated_number value = unpack_storage_number(n);
        sum += value;

        counter++;
    }
    rd->state->query_ops.finalize(&handle);
    if(unlikely(!counter)) {
        debug(D_BACKEND, "BACKEND: %s.%s.%s: no values stored in database for range %lu to %lu",
              host->hostname, st->id, rd->id,
              (unsigned long)after, (unsigned long)before
        );
        return NAN;
    }

    if(unlikely(BACKEND_OPTIONS_DATA_SOURCE(backend_options) == BACKEND_SOURCE_DATA_SUM))
        return sum;

    return sum / (calculated_number)counter;
}