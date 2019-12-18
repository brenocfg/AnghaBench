#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int usec_t ;
typedef  unsigned int uint64_t ;
typedef  int uint32_t ;
typedef  int time_t ;
struct TYPE_4__ {int /*<<< orphan*/  metric_API_consumers; } ;
struct rrdengine_instance {TYPE_1__ stats; } ;
struct rrdeng_query_handle {int next_page_time; int position; int now; struct rrdeng_page_descr* descr; TYPE_3__* page_index; struct rrdengine_instance* ctx; } ;
struct rrdeng_page_descr {int start_time; TYPE_2__* pg_cache_descr; } ;
struct rrddim_query_handle {int end_time; struct rrdeng_query_handle rrdeng; } ;
typedef  int /*<<< orphan*/  storage_number ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int INVALID_TIME ; 
 int /*<<< orphan*/  SN_EMPTY_SLOT ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  pg_cache_atomic_get_pg_info (struct rrdeng_page_descr*,int*,int*) ; 
 struct rrdeng_page_descr* pg_cache_lookup_next (struct rrdengine_instance*,TYPE_3__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pg_cache_put (struct rrdengine_instance*,struct rrdeng_page_descr*) ; 
 int /*<<< orphan*/  rrd_stat_atomic_add (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

storage_number rrdeng_load_metric_next(struct rrddim_query_handle *rrdimm_handle, time_t *current_time)
{
    struct rrdeng_query_handle *handle;
    struct rrdengine_instance *ctx;
    struct rrdeng_page_descr *descr;
    storage_number *page, ret;
    unsigned position, entries;
    usec_t next_page_time, current_position_time, page_end_time;
    uint32_t page_length;

    handle = &rrdimm_handle->rrdeng;
    if (unlikely(INVALID_TIME == handle->next_page_time)) {
        return SN_EMPTY_SLOT;
    }
    ctx = handle->ctx;
    if (unlikely(NULL == (descr = handle->descr))) {
        /* it's the first call */
        next_page_time = handle->next_page_time * USEC_PER_SEC;
    } else {
        pg_cache_atomic_get_pg_info(descr, &page_end_time, &page_length);
    }
    position = handle->position + 1;

    if (unlikely(NULL == descr ||
                 position >= (page_length / sizeof(storage_number)))) {
        /* We need to get a new page */
        if (descr) {
            /* Drop old page's reference */
            handle->next_page_time = (page_end_time / USEC_PER_SEC) + 1;
            if (unlikely(handle->next_page_time > rrdimm_handle->end_time)) {
                goto no_more_metrics;
            }
            next_page_time = handle->next_page_time * USEC_PER_SEC;
#ifdef NETDATA_INTERNAL_CHECKS
            rrd_stat_atomic_add(&ctx->stats.metric_API_consumers, -1);
#endif
            pg_cache_put(ctx, descr);
            handle->descr = NULL;
        }
        descr = pg_cache_lookup_next(ctx, handle->page_index, &handle->page_index->id,
                                     next_page_time, rrdimm_handle->end_time * USEC_PER_SEC);
        if (NULL == descr) {
            goto no_more_metrics;
        }
#ifdef NETDATA_INTERNAL_CHECKS
        rrd_stat_atomic_add(&ctx->stats.metric_API_consumers, 1);
#endif
        handle->descr = descr;
        pg_cache_atomic_get_pg_info(descr, &page_end_time, &page_length);
        if (unlikely(INVALID_TIME == descr->start_time ||
                     INVALID_TIME == page_end_time)) {
            goto no_more_metrics;
        }
        if (unlikely(descr->start_time != page_end_time && next_page_time > descr->start_time)) {
            /* we're in the middle of the page somewhere */
            entries = page_length / sizeof(storage_number);
            position = ((uint64_t)(next_page_time - descr->start_time)) * (entries - 1) /
                       (page_end_time - descr->start_time);
        } else {
            position = 0;
        }
    }
    page = descr->pg_cache_descr->page;
    ret = page[position];
    entries = page_length / sizeof(storage_number);
    if (entries > 1) {
        usec_t dt;

        dt = (page_end_time - descr->start_time) / (entries - 1);
        current_position_time = descr->start_time + position * dt;
    } else {
        current_position_time = descr->start_time;
    }
    handle->position = position;
    handle->now = current_position_time / USEC_PER_SEC;
/*  assert(handle->now >= rrdimm_handle->start_time && handle->now <= rrdimm_handle->end_time);
    The above assertion is an approximation and needs to take update_every into account */
    if (unlikely(handle->now >= rrdimm_handle->end_time)) {
        /* next calls will not load any more metrics */
        handle->next_page_time = INVALID_TIME;
    }
    *current_time = handle->now;
    return ret;

no_more_metrics:
    handle->next_page_time = INVALID_TIME;
    return SN_EMPTY_SLOT;
}