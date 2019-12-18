#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
struct rrdeng_collect_handle {struct pg_cache_page_index* page_index; } ;
struct pg_cache_page_index {int oldest_time; } ;
struct TYPE_7__ {TYPE_2__* state; } ;
struct TYPE_5__ {struct rrdeng_collect_handle rrdeng; } ;
struct TYPE_6__ {TYPE_1__ handle; } ;
typedef  TYPE_3__ RRDDIM ;

/* Variables and functions */
 int USEC_PER_SEC ; 

time_t rrdeng_metric_oldest_time(RRDDIM *rd)
{
    struct rrdeng_collect_handle *handle;
    struct pg_cache_page_index *page_index;

    handle = &rd->state->handle.rrdeng;
    page_index = handle->page_index;

    return page_index->oldest_time / USEC_PER_SEC;
}