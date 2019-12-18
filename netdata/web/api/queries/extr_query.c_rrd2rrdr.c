#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct rrdeng_region_info {int update_every; } ;
struct TYPE_8__ {int update_every; scalar_t__ rrd_memory_mode; } ;
typedef  TYPE_1__ RRDSET ;
typedef  int /*<<< orphan*/  RRDR_OPTIONS ;
typedef  int /*<<< orphan*/  RRDR_GROUPING ;
typedef  int /*<<< orphan*/  RRDR ;

/* Variables and functions */
 scalar_t__ RRD_MEMORY_MODE_DBENGINE ; 
 int /*<<< orphan*/  freez (struct rrdeng_region_info*) ; 
 int /*<<< orphan*/ * rrd2rrdr_fixedstep (TYPE_1__*,long,long long,long long,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * rrd2rrdr_variablestep (TYPE_1__*,long,long long,long long,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct rrdeng_region_info*) ; 
 unsigned int rrdeng_variable_step_boundaries (TYPE_1__*,long long,long long,struct rrdeng_region_info**,unsigned int*) ; 
 int rrdr_convert_before_after_to_absolute (long long*,long long*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_first_entry_t (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdset_last_entry_t (TYPE_1__*) ; 

RRDR *rrd2rrdr(
        RRDSET *st
        , long points_requested
        , long long after_requested
        , long long before_requested
        , RRDR_GROUPING group_method
        , long resampling_time_requested
        , RRDR_OPTIONS options
        , const char *dimensions
) {
    int rrd_update_every;
    int absolute_period_requested;
    time_t first_entry_t = rrdset_first_entry_t(st);
    time_t last_entry_t  = rrdset_last_entry_t(st);

    rrd_update_every = st->update_every;
    absolute_period_requested = rrdr_convert_before_after_to_absolute(&after_requested, &before_requested,
                                                                      rrd_update_every, first_entry_t,
                                                                      last_entry_t);
#ifdef ENABLE_DBENGINE
    if (st->rrd_memory_mode == RRD_MEMORY_MODE_DBENGINE) {
        struct rrdeng_region_info *region_info_array;
        unsigned regions, max_interval;

        /* This call takes the chart read-lock */
        regions = rrdeng_variable_step_boundaries(st, after_requested, before_requested,
                                                  &region_info_array, &max_interval);
        if (1 == regions) {
            if (region_info_array) {
                if (rrd_update_every != region_info_array[0].update_every) {
                    rrd_update_every = region_info_array[0].update_every;
                    /* recalculate query alignment */
                    absolute_period_requested =
                            rrdr_convert_before_after_to_absolute(&after_requested, &before_requested, rrd_update_every,
                                                                  first_entry_t, last_entry_t);
                }
                freez(region_info_array);
            }
            return rrd2rrdr_fixedstep(st, points_requested, after_requested, before_requested, group_method,
                                      resampling_time_requested, options, dimensions, rrd_update_every,
                                      first_entry_t, last_entry_t, absolute_period_requested);
        } else {
            if (rrd_update_every != (uint16_t)max_interval) {
                rrd_update_every = (uint16_t) max_interval;
                /* recalculate query alignment */
                absolute_period_requested = rrdr_convert_before_after_to_absolute(&after_requested, &before_requested,
                                                                                  rrd_update_every, first_entry_t,
                                                                                  last_entry_t);
            }
            return rrd2rrdr_variablestep(st, points_requested, after_requested, before_requested, group_method,
                                         resampling_time_requested, options, dimensions, rrd_update_every,
                                         first_entry_t, last_entry_t, absolute_period_requested, region_info_array);
        }
    }
#endif
    return rrd2rrdr_fixedstep(st, points_requested, after_requested, before_requested, group_method,
                              resampling_time_requested, options, dimensions,
                              rrd_update_every, first_entry_t, last_entry_t, absolute_period_requested);
}