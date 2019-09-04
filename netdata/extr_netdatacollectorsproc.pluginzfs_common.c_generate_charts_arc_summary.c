#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long long hits; unsigned long long misses; unsigned long long mfu_hits; unsigned long long mru_hits; unsigned long long size; unsigned long long p; unsigned long long c; unsigned long long memory_direct_count; unsigned long long memory_throttle_count; unsigned long long memory_indirect_count; unsigned long long deleted; unsigned long long evict_skip; unsigned long long mutex_miss; unsigned long long hash_collisions; unsigned long long demand_data_hits; unsigned long long demand_data_misses; unsigned long long prefetch_data_hits; unsigned long long prefetch_data_misses; unsigned long long hash_elements; unsigned long long hash_elements_max; unsigned long long hash_chains; unsigned long long hash_chain_max; } ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 int CONFIG_BOOLEAN_YES ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_ZFS_ACTUAL_HITS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_ZFS_ARC_SIZE_BREAKDOWN ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_ZFS_DEMAND_DATA_HITS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_ZFS_HASH_CHAINS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_ZFS_HASH_ELEMENTS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_ZFS_IMPORTANT_OPS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_ZFS_MEMORY_OPS ; 
 int /*<<< orphan*/  NETDATA_CHART_PRIO_ZFS_PREFETCH_DATA_HITS ; 
 int /*<<< orphan*/  RRDSET_TYPE_LINE ; 
 int /*<<< orphan*/  RRDSET_TYPE_STACKED ; 
 int /*<<< orphan*/  RRD_ALGORITHM_ABSOLUTE ; 
 int /*<<< orphan*/  RRD_ALGORITHM_INCREMENTAL ; 
 int /*<<< orphan*/  RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL ; 
 int /*<<< orphan*/  RRD_ALGORITHM_PCENT_OVER_ROW_TOTAL ; 
 int /*<<< orphan*/  ZFS_FAMILY_EFFICIENCY ; 
 int /*<<< orphan*/  ZFS_FAMILY_HASH ; 
 int /*<<< orphan*/  ZFS_FAMILY_OPERATIONS ; 
 TYPE_1__ arcstats ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/ * rrddim_add (int /*<<< orphan*/ *,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrddim_set_by_pointer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long long) ; 
 int /*<<< orphan*/ * rrdset_create_localhost (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,char const*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrdset_next (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void generate_charts_arc_summary(const char *plugin, const char *module, int show_zero_charts, int update_every) {
    static int do_arc_size_breakdown = -1, do_memory = -1, do_important_ops = -1, do_actual_hits = -1, \
               do_demand_data_hits = -1, do_prefetch_data_hits = -1, do_hash_elements = -1, do_hash_chains = -1;

    if(unlikely(do_arc_size_breakdown == -1))
        do_arc_size_breakdown = do_memory = do_important_ops = do_actual_hits = do_demand_data_hits \
        = do_prefetch_data_hits = do_hash_elements = do_hash_chains = show_zero_charts;

    unsigned long long arc_accesses_total = arcstats.hits + arcstats.misses;
    unsigned long long real_hits = arcstats.mfu_hits + arcstats.mru_hits;
    unsigned long long real_misses = arc_accesses_total - real_hits;

    //unsigned long long anon_hits = arcstats.hits - (arcstats.mfu_hits + arcstats.mru_hits + arcstats.mfu_ghost_hits + arcstats.mru_ghost_hits);

    unsigned long long arc_size = arcstats.size;
    unsigned long long mru_size = arcstats.p;
    //unsigned long long target_min_size = arcstats.c_min;
    //unsigned long long target_max_size = arcstats.c_max;
    unsigned long long target_size = arcstats.c;
    //unsigned long long target_size_ratio = (target_max_size / target_min_size);

    unsigned long long mfu_size;
    if(arc_size > target_size)
        mfu_size = arc_size - mru_size;
    else
        mfu_size = target_size - mru_size;

    // --------------------------------------------------------------------

    if(likely(do_arc_size_breakdown == CONFIG_BOOLEAN_YES || mru_size || mfu_size)) {
        do_arc_size_breakdown = CONFIG_BOOLEAN_YES;

        static RRDSET *st_arc_size_breakdown = NULL;
        static RRDDIM *rd_most_recent = NULL;
        static RRDDIM *rd_most_frequent = NULL;

        if (unlikely(!st_arc_size_breakdown)) {
            st_arc_size_breakdown = rrdset_create_localhost(
                    "zfs"
                    , "arc_size_breakdown"
                    , NULL
                    , ZFS_FAMILY_EFFICIENCY
                    , NULL
                    , "ZFS ARC Size Breakdown"
                    , "percentage"
                    , plugin
                    , module
                    , NETDATA_CHART_PRIO_ZFS_ARC_SIZE_BREAKDOWN
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

            rd_most_recent   = rrddim_add(st_arc_size_breakdown, "recent", NULL,   1, 1, RRD_ALGORITHM_PCENT_OVER_ROW_TOTAL);
            rd_most_frequent = rrddim_add(st_arc_size_breakdown, "frequent", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_ROW_TOTAL);
        }
        else
            rrdset_next(st_arc_size_breakdown);

        rrddim_set_by_pointer(st_arc_size_breakdown, rd_most_recent,   mru_size);
        rrddim_set_by_pointer(st_arc_size_breakdown, rd_most_frequent, mfu_size);
        rrdset_done(st_arc_size_breakdown);
    }

    // --------------------------------------------------------------------

    if(likely(do_memory == CONFIG_BOOLEAN_YES || arcstats.memory_direct_count \
                                              || arcstats.memory_throttle_count \
                                              || arcstats.memory_indirect_count)) {
        do_memory = CONFIG_BOOLEAN_YES;

        static RRDSET *st_memory = NULL;
#ifndef __FreeBSD__
        static RRDDIM *rd_direct = NULL;
#endif
        static RRDDIM *rd_throttled = NULL;
#ifndef __FreeBSD__
        static RRDDIM *rd_indirect = NULL;
#endif

        if (unlikely(!st_memory)) {
            st_memory = rrdset_create_localhost(
                    "zfs"
                    , "memory_ops"
                    , NULL
                    , ZFS_FAMILY_OPERATIONS
                    , NULL
                    , "ZFS Memory Operations"
                    , "operations/s"
                    , plugin
                    , module
                    , NETDATA_CHART_PRIO_ZFS_MEMORY_OPS
                    , update_every
                    , RRDSET_TYPE_LINE
            );

#ifndef __FreeBSD__
            rd_direct    = rrddim_add(st_memory, "direct",    NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
#endif
            rd_throttled = rrddim_add(st_memory, "throttled", NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
#ifndef __FreeBSD__
            rd_indirect  = rrddim_add(st_memory, "indirect",  NULL, 1, 1, RRD_ALGORITHM_INCREMENTAL);
#endif
        }
        else
            rrdset_next(st_memory);

#ifndef __FreeBSD__
        rrddim_set_by_pointer(st_memory, rd_direct,    arcstats.memory_direct_count);
#endif
        rrddim_set_by_pointer(st_memory, rd_throttled, arcstats.memory_throttle_count);
#ifndef __FreeBSD__
        rrddim_set_by_pointer(st_memory, rd_indirect,  arcstats.memory_indirect_count);
#endif
        rrdset_done(st_memory);
    }

    // --------------------------------------------------------------------

    if(likely(do_important_ops == CONFIG_BOOLEAN_YES || arcstats.deleted \
                                                     || arcstats.evict_skip \
                                                     || arcstats.mutex_miss \
                                                     || arcstats.hash_collisions)) {
        do_important_ops = CONFIG_BOOLEAN_YES;

        static RRDSET *st_important_ops = NULL;
        static RRDDIM *rd_deleted = NULL;
        static RRDDIM *rd_mutex_misses = NULL;
        static RRDDIM *rd_evict_skips = NULL;
        static RRDDIM *rd_hash_collisions = NULL;

        if (unlikely(!st_important_ops)) {
            st_important_ops = rrdset_create_localhost(
                    "zfs"
                    , "important_ops"
                    , NULL
                    , ZFS_FAMILY_OPERATIONS
                    , NULL
                    , "ZFS Important Operations"
                    , "operations/s"
                    , plugin
                    , module
                    , NETDATA_CHART_PRIO_ZFS_IMPORTANT_OPS
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_evict_skips     = rrddim_add(st_important_ops, "eskip",   "evict skip", 1, 1, RRD_ALGORITHM_INCREMENTAL);
            rd_deleted         = rrddim_add(st_important_ops, "deleted", NULL,         1, 1, RRD_ALGORITHM_INCREMENTAL);
            rd_mutex_misses    = rrddim_add(st_important_ops, "mtxmis",  "mutex miss", 1, 1, RRD_ALGORITHM_INCREMENTAL);
            rd_hash_collisions = rrddim_add(st_important_ops, "hash_collisions", "hash collisions", 1, 1, RRD_ALGORITHM_INCREMENTAL);
        }
        else
            rrdset_next(st_important_ops);

        rrddim_set_by_pointer(st_important_ops, rd_deleted,      arcstats.deleted);
        rrddim_set_by_pointer(st_important_ops, rd_evict_skips,  arcstats.evict_skip);
        rrddim_set_by_pointer(st_important_ops, rd_mutex_misses, arcstats.mutex_miss);
        rrddim_set_by_pointer(st_important_ops, rd_hash_collisions, arcstats.hash_collisions);
        rrdset_done(st_important_ops);
    }

    // --------------------------------------------------------------------

    if(likely(do_actual_hits == CONFIG_BOOLEAN_YES || real_hits || real_misses)) {
        do_actual_hits = CONFIG_BOOLEAN_YES;

        static RRDSET *st_actual_hits = NULL;
        static RRDDIM *rd_actual_hits = NULL;
        static RRDDIM *rd_actual_misses = NULL;

        if (unlikely(!st_actual_hits)) {
            st_actual_hits = rrdset_create_localhost(
                    "zfs"
                    , "actual_hits"
                    , NULL
                    , ZFS_FAMILY_EFFICIENCY
                    , NULL
                    , "ZFS Actual Cache Hits"
                    , "percentage"
                    , plugin
                    , module
                    , NETDATA_CHART_PRIO_ZFS_ACTUAL_HITS
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

            rd_actual_hits   = rrddim_add(st_actual_hits, "hits", NULL,   1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
            rd_actual_misses = rrddim_add(st_actual_hits, "misses", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
        }
        else
            rrdset_next(st_actual_hits);

        rrddim_set_by_pointer(st_actual_hits, rd_actual_hits,   real_hits);
        rrddim_set_by_pointer(st_actual_hits, rd_actual_misses, real_misses);
        rrdset_done(st_actual_hits);
    }

    // --------------------------------------------------------------------

    if(likely(do_demand_data_hits == CONFIG_BOOLEAN_YES || arcstats.demand_data_hits || arcstats.demand_data_misses)) {
        do_demand_data_hits = CONFIG_BOOLEAN_YES;

        static RRDSET *st_demand_data_hits = NULL;
        static RRDDIM *rd_demand_data_hits = NULL;
        static RRDDIM *rd_demand_data_misses = NULL;

        if (unlikely(!st_demand_data_hits)) {
            st_demand_data_hits = rrdset_create_localhost(
                    "zfs"
                    , "demand_data_hits"
                    , NULL
                    , ZFS_FAMILY_EFFICIENCY
                    , NULL
                    , "ZFS Data Demand Efficiency"
                    , "percentage"
                    , plugin
                    , module
                    , NETDATA_CHART_PRIO_ZFS_DEMAND_DATA_HITS
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

            rd_demand_data_hits   = rrddim_add(st_demand_data_hits, "hits", NULL,   1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
            rd_demand_data_misses = rrddim_add(st_demand_data_hits, "misses", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
        }
        else
            rrdset_next(st_demand_data_hits);

        rrddim_set_by_pointer(st_demand_data_hits, rd_demand_data_hits,   arcstats.demand_data_hits);
        rrddim_set_by_pointer(st_demand_data_hits, rd_demand_data_misses, arcstats.demand_data_misses);
        rrdset_done(st_demand_data_hits);
    }

    // --------------------------------------------------------------------

    if(likely(do_prefetch_data_hits == CONFIG_BOOLEAN_YES || arcstats.prefetch_data_hits \
                                                          || arcstats.prefetch_data_misses)) {
        do_prefetch_data_hits = CONFIG_BOOLEAN_YES;

        static RRDSET *st_prefetch_data_hits = NULL;
        static RRDDIM *rd_prefetch_data_hits = NULL;
        static RRDDIM *rd_prefetch_data_misses = NULL;

        if (unlikely(!st_prefetch_data_hits)) {
            st_prefetch_data_hits = rrdset_create_localhost(
                    "zfs"
                    , "prefetch_data_hits"
                    , NULL
                    , ZFS_FAMILY_EFFICIENCY
                    , NULL
                    , "ZFS Data Prefetch Efficiency"
                    , "percentage"
                    , plugin
                    , module
                    , NETDATA_CHART_PRIO_ZFS_PREFETCH_DATA_HITS
                    , update_every
                    , RRDSET_TYPE_STACKED
            );

            rd_prefetch_data_hits   = rrddim_add(st_prefetch_data_hits, "hits", NULL,   1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
            rd_prefetch_data_misses = rrddim_add(st_prefetch_data_hits, "misses", NULL, 1, 1, RRD_ALGORITHM_PCENT_OVER_DIFF_TOTAL);
        }
        else
            rrdset_next(st_prefetch_data_hits);

        rrddim_set_by_pointer(st_prefetch_data_hits, rd_prefetch_data_hits,   arcstats.prefetch_data_hits);
        rrddim_set_by_pointer(st_prefetch_data_hits, rd_prefetch_data_misses, arcstats.prefetch_data_misses);
        rrdset_done(st_prefetch_data_hits);
    }

    // --------------------------------------------------------------------

    if(likely(do_hash_elements == CONFIG_BOOLEAN_YES || arcstats.hash_elements || arcstats.hash_elements_max)) {
        do_hash_elements = CONFIG_BOOLEAN_YES;

        static RRDSET *st_hash_elements = NULL;
        static RRDDIM *rd_hash_elements_current = NULL;
        static RRDDIM *rd_hash_elements_max = NULL;

        if (unlikely(!st_hash_elements)) {
            st_hash_elements = rrdset_create_localhost(
                    "zfs"
                    , "hash_elements"
                    , NULL
                    , ZFS_FAMILY_HASH
                    , NULL
                    , "ZFS ARC Hash Elements"
                    , "elements"
                    , plugin
                    , module
                    , NETDATA_CHART_PRIO_ZFS_HASH_ELEMENTS
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_hash_elements_current = rrddim_add(st_hash_elements, "current", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
            rd_hash_elements_max     = rrddim_add(st_hash_elements, "max",     NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else
            rrdset_next(st_hash_elements);

        rrddim_set_by_pointer(st_hash_elements, rd_hash_elements_current, arcstats.hash_elements);
        rrddim_set_by_pointer(st_hash_elements, rd_hash_elements_max, arcstats.hash_elements_max);
        rrdset_done(st_hash_elements);
    }

    // --------------------------------------------------------------------

    if(likely(do_hash_chains == CONFIG_BOOLEAN_YES || arcstats.hash_chains || arcstats.hash_chain_max)) {
        do_hash_chains = CONFIG_BOOLEAN_YES;

        static RRDSET *st_hash_chains = NULL;
        static RRDDIM *rd_hash_chains_current = NULL;
        static RRDDIM *rd_hash_chains_max = NULL;

        if (unlikely(!st_hash_chains)) {
            st_hash_chains = rrdset_create_localhost(
                    "zfs"
                    , "hash_chains"
                    , NULL
                    , ZFS_FAMILY_HASH
                    , NULL
                    , "ZFS ARC Hash Chains"
                    , "chains"
                    , plugin
                    , module
                    , NETDATA_CHART_PRIO_ZFS_HASH_CHAINS
                    , update_every
                    , RRDSET_TYPE_LINE
            );

            rd_hash_chains_current = rrddim_add(st_hash_chains, "current", NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
            rd_hash_chains_max     = rrddim_add(st_hash_chains, "max",     NULL, 1, 1, RRD_ALGORITHM_ABSOLUTE);
        }
        else
            rrdset_next(st_hash_chains);

        rrddim_set_by_pointer(st_hash_chains, rd_hash_chains_current, arcstats.hash_chains);
        rrddim_set_by_pointer(st_hash_chains, rd_hash_chains_max, arcstats.hash_chain_max);
        rrdset_done(st_hash_chains);
    }

    // --------------------------------------------------------------------

}