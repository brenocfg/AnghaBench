#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ usec_t ;
struct rrdeng_page_descr {scalar_t__ start_time; scalar_t__ end_time; } ;
struct pg_cache_page_index {scalar_t__ oldest_time; scalar_t__ latest_time; } ;

/* Variables and functions */
 scalar_t__ INVALID_TIME ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

void pg_cache_add_new_metric_time(struct pg_cache_page_index *page_index, struct rrdeng_page_descr *descr)
{
    usec_t oldest_time = page_index->oldest_time;
    usec_t latest_time = page_index->latest_time;

    if (unlikely(oldest_time == INVALID_TIME || descr->start_time < oldest_time)) {
        page_index->oldest_time = descr->start_time;
    }
    if (likely(descr->end_time > latest_time || latest_time == INVALID_TIME)) {
        page_index->latest_time = descr->end_time;
    }
}