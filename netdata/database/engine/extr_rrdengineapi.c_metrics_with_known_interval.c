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
struct rrdeng_page_descr {scalar_t__ start_time; scalar_t__ end_time; int page_length; } ;
typedef  int /*<<< orphan*/  storage_number ;

/* Variables and functions */
 scalar_t__ INVALID_TIME ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int metrics_with_known_interval(struct rrdeng_page_descr *descr)
{
    unsigned page_entries;

    if (unlikely(INVALID_TIME == descr->start_time || INVALID_TIME == descr->end_time))
        return 0;
    page_entries = descr->page_length / sizeof(storage_number);
    if (likely(page_entries > 1)) {
        return 1;
    }
    return 0;
}