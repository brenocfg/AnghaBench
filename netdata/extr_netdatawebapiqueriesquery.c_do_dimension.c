#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  storage_number ;
typedef  double calculated_number ;
struct TYPE_14__ {int /*<<< orphan*/ * values; } ;
struct TYPE_11__ {double (* grouping_flush ) (TYPE_3__*,int /*<<< orphan*/ *) ;size_t db_points_read; long result_points_generated; int /*<<< orphan*/  (* grouping_add ) (TYPE_3__*,double) ;} ;
struct TYPE_13__ {long group; double min; double max; long d; double* v; TYPE_2__* st; scalar_t__ after; scalar_t__ before; TYPE_1__ internal; int /*<<< orphan*/ * od; int /*<<< orphan*/ * o; } ;
struct TYPE_12__ {scalar_t__ update_every; long entries; } ;
typedef  TYPE_2__ RRDSET ;
typedef  int /*<<< orphan*/  RRDR_VALUE_FLAGS ;
typedef  TYPE_3__ RRDR ;
typedef  TYPE_4__ RRDDIM ;

/* Variables and functions */
 double NAN ; 
 int /*<<< orphan*/  RRDR_DIMENSION_NONZERO ; 
 int /*<<< orphan*/  RRDR_VALUE_NOTHING ; 
 int /*<<< orphan*/  RRDR_VALUE_RESET ; 
 int did_storage_number_reset (int /*<<< orphan*/ ) ; 
 int does_storage_number_exist (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rrdr_done (TYPE_3__*,long) ; 
 long rrdr_line_init (TYPE_3__*,scalar_t__,long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,double) ; 
 double stub2 (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 double unpack_storage_number (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void do_dimension(
          RRDR *r
        , long points_wanted
        , RRDDIM *rd
        , long dim_id_in_rrdr
        , long after_slot
        , long before_slot
        , time_t after_wanted
        , time_t before_wanted
){
    (void) before_slot;

    RRDSET *st = r->st;

    time_t
        now = after_wanted,
        dt = st->update_every,
        max_date = 0,
        min_date = 0;

    long
        slot = after_slot,
        group_size = r->group,
        points_added = 0,
        values_in_group = 0,
        values_in_group_non_zero = 0,
        rrdr_line = -1,
        entries = st->entries;

    RRDR_VALUE_FLAGS
        group_value_flags = RRDR_VALUE_NOTHING;

    calculated_number min = r->min, max = r->max;
    size_t db_points_read = 0;
    for( ; points_added < points_wanted ; now += dt, slot++ ) {
        if(unlikely(slot >= entries)) slot = 0;

        // make sure we return data in the proper time range
        if(unlikely(now > before_wanted)) {
            #ifdef NETDATA_INTERNAL_CHECKS
            r->internal.log = "stopped, because attempted to access the db after 'wanted before'";
            #endif
            break;
        }
        if(unlikely(now < after_wanted)) {
            #ifdef NETDATA_INTERNAL_CHECKS
            r->internal.log = "skipped, because attempted to access the db before 'wanted after'";
            #endif
            continue;
        }

        // read the value from the database
        storage_number n = rd->values[slot];
        calculated_number value = NAN;
        if(likely(does_storage_number_exist(n))) {

            value = unpack_storage_number(n);
            if(likely(value != 0.0))
                values_in_group_non_zero++;

            if(unlikely(did_storage_number_reset(n)))
                group_value_flags |= RRDR_VALUE_RESET;

        }

        // add this value for grouping
        r->internal.grouping_add(r, value);
        values_in_group++;
        db_points_read++;

        if(unlikely(values_in_group == group_size)) {
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
            calculated_number value = r->internal.grouping_flush(r, rrdr_value_options_ptr);
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
    }

    r->internal.db_points_read += db_points_read;
    r->internal.result_points_generated += points_added;

    r->min = min;
    r->max = max;
    r->before = max_date;
    r->after = min_date - (r->group - 1) * r->st->update_every;
    rrdr_done(r, rrdr_line);

    #ifdef NETDATA_INTERNAL_CHECKS
    if(unlikely(r->rows != points_added))
        error("INTERNAL ERROR: %s.%s added %zu rows, but RRDR says I added %zu.", r->st->name, rd->name, (size_t)points_added, (size_t)r->rows);
    #endif
}