#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct rrddim_query_handle {int dummy; } ;
typedef  int /*<<< orphan*/  storage_number ;
typedef  double calculated_number ;
struct TYPE_20__ {char* name; TYPE_2__* state; } ;
struct TYPE_17__ {char* log; double (* grouping_flush ) (TYPE_5__*,int /*<<< orphan*/ *) ;size_t db_points_read; long result_points_generated; int /*<<< orphan*/  (* grouping_add ) (TYPE_5__*,double) ;} ;
struct TYPE_19__ {scalar_t__ update_every; double min; double max; long d; double* v; int group; long rows; TYPE_4__* st; scalar_t__ after; scalar_t__ before; TYPE_3__ internal; int /*<<< orphan*/ * od; int /*<<< orphan*/ * o; } ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* finalize ) (struct rrddim_query_handle*) ;int /*<<< orphan*/  (* next_metric ) (struct rrddim_query_handle*,scalar_t__*) ;int /*<<< orphan*/  (* is_finished ) (struct rrddim_query_handle*) ;int /*<<< orphan*/  (* init ) (TYPE_6__*,struct rrddim_query_handle*,scalar_t__,scalar_t__) ;} ;
struct TYPE_16__ {TYPE_1__ query_ops; } ;
typedef  int /*<<< orphan*/  RRDR_VALUE_FLAGS ;
typedef  TYPE_5__ RRDR ;
typedef  TYPE_6__ RRDDIM ;

/* Variables and functions */
 double NAN ; 
 int /*<<< orphan*/  RRDR_DIMENSION_NONZERO ; 
 int /*<<< orphan*/  RRDR_VALUE_NOTHING ; 
 int /*<<< orphan*/  RRDR_VALUE_RESET ; 
 int /*<<< orphan*/  SN_EMPTY_SLOT ; 
 int did_storage_number_reset (int /*<<< orphan*/ ) ; 
 int does_storage_number_exist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rrdr_done (TYPE_5__*,long) ; 
 long rrdr_line_init (TYPE_5__*,scalar_t__,long) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,struct rrddim_query_handle*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct rrddim_query_handle*) ; 
 int /*<<< orphan*/  stub3 (struct rrddim_query_handle*,scalar_t__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_5__*,double) ; 
 int /*<<< orphan*/  stub5 (TYPE_5__*,double) ; 
 double stub6 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (struct rrddim_query_handle*) ; 
 scalar_t__ unlikely (int) ; 
 double unpack_storage_number (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void do_dimension_variablestep(
          RRDR *r
        , long points_wanted
        , RRDDIM *rd
        , long dim_id_in_rrdr
        , time_t after_wanted
        , time_t before_wanted
){
//  RRDSET *st = r->st;

    time_t
        now = after_wanted,
        dt = r->update_every,
        max_date = 0,
        min_date = 0;

    long
//      group_size = r->group,
        points_added = 0,
        values_in_group = 0,
        values_in_group_non_zero = 0,
        rrdr_line = -1;

    RRDR_VALUE_FLAGS
        group_value_flags = RRDR_VALUE_NOTHING;

    struct rrddim_query_handle handle;

    calculated_number min = r->min, max = r->max;
    size_t db_points_read = 0;
    time_t db_now = now;
    storage_number n_curr, n_prev = SN_EMPTY_SLOT;
    calculated_number value;

    for(rd->state->query_ops.init(rd, &handle, now, before_wanted) ; points_added < points_wanted ; now += dt) {
        // make sure we return data in the proper time range
        if (unlikely(now > before_wanted)) {
#ifdef NETDATA_INTERNAL_CHECKS
            r->internal.log = "stopped, because attempted to access the db after 'wanted before'";
#endif
            break;
        }
        if (unlikely(now < after_wanted)) {
#ifdef NETDATA_INTERNAL_CHECKS
            r->internal.log = "skipped, because attempted to access the db before 'wanted after'";
#endif
            continue;
        }

        while (now >= db_now && (!rd->state->query_ops.is_finished(&handle) ||
                                 does_storage_number_exist(n_prev))) {
            value = NAN;
            if (does_storage_number_exist(n_prev)) {
                // use the previously read database value
                n_curr = n_prev;
            } else {
                // read the value from the database
                n_curr = rd->state->query_ops.next_metric(&handle, &db_now);
            }
            n_prev = SN_EMPTY_SLOT;
            // db_now has a different value than above
            if (likely(now >= db_now)) {
                if (likely(does_storage_number_exist(n_curr))) {
                    value = unpack_storage_number(n_curr);
                    if (likely(value != 0.0))
                        values_in_group_non_zero++;

                    if (unlikely(did_storage_number_reset(n_curr)))
                        group_value_flags |= RRDR_VALUE_RESET;
                }
            } else {
                // We must postpone processing the value and fill the result with gaps instead
                if (likely(does_storage_number_exist(n_curr))) {
                    n_prev = n_curr;
                }
            }
            // add this value to grouping
            r->internal.grouping_add(r, value);
            values_in_group++;
            db_points_read++;
        }

        if (0 == values_in_group) {
            // add NAN to grouping
            r->internal.grouping_add(r, NAN);
        }

        rrdr_line = rrdr_line_init(r, now, rrdr_line);

        if(unlikely(!min_date)) min_date = now;
        max_date = now;

        // find the place to store our values
        RRDR_VALUE_FLAGS *rrdr_value_options_ptr = &r->o[rrdr_line * r->d + dim_id_in_rrdr];

        // update the dimension options
        if(likely(values_in_group_non_zero))
            r->od[dim_id_in_rrdr] |= RRDR_DIMENSION_NONZERO;

        // store the specific point options
        *rrdr_value_options_ptr = group_value_flags;

        // store the value
        value = r->internal.grouping_flush(r, rrdr_value_options_ptr);
        r->v[rrdr_line * r->d + dim_id_in_rrdr] = value;

        if(likely(points_added || dim_id_in_rrdr)) {
            // find the min/max across all dimensions

            if(unlikely(value < min)) min = value;
            if(unlikely(value > max)) max = value;

        }
        else {
            // runs only when dim_id_in_rrdr == 0 && points_added == 0
            // so, on the first point added for the query.
            min = max = value;
        }

        points_added++;
        values_in_group = 0;
        group_value_flags = RRDR_VALUE_NOTHING;
        values_in_group_non_zero = 0;
    }
    rd->state->query_ops.finalize(&handle);

    r->internal.db_points_read += db_points_read;
    r->internal.result_points_generated += points_added;

    r->min = min;
    r->max = max;
    r->before = max_date;
    r->after = min_date - (r->group - 1) * dt;
    rrdr_done(r, rrdr_line);

    #ifdef NETDATA_INTERNAL_CHECKS
    if(unlikely(r->rows != points_added))
        error("INTERNAL ERROR: %s.%s added %zu rows, but RRDR says I added %zu.", r->st->name, rd->name, (size_t)points_added, (size_t)r->rows);
    #endif
}