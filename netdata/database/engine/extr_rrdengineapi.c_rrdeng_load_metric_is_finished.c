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
struct rrdeng_query_handle {scalar_t__ next_page_time; } ;
struct rrddim_query_handle {struct rrdeng_query_handle rrdeng; } ;

/* Variables and functions */
 scalar_t__ INVALID_TIME ; 

int rrdeng_load_metric_is_finished(struct rrddim_query_handle *rrdimm_handle)
{
    struct rrdeng_query_handle *handle;

    handle = &rrdimm_handle->rrdeng;
    return (INVALID_TIME == handle->next_page_time);
}