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

/* Variables and functions */

__attribute__((used)) static inline int is_page_in_time_range(struct rrdeng_page_descr *descr, usec_t start_time, usec_t end_time)
{
    usec_t pg_start, pg_end;

    pg_start = descr->start_time;
    pg_end = descr->end_time;

    return (pg_start < start_time && pg_end >= start_time) ||
           (pg_start >= start_time && pg_start <= end_time);
}