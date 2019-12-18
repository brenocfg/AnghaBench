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
struct rrdeng_page_descr {int /*<<< orphan*/ * pg_cache_descr; scalar_t__ pg_cache_descr_state; int /*<<< orphan*/ * extent; int /*<<< orphan*/ * id; void* end_time; void* start_time; scalar_t__ page_length; } ;

/* Variables and functions */
 void* INVALID_TIME ; 
 struct rrdeng_page_descr* mallocz (int) ; 

struct rrdeng_page_descr *pg_cache_create_descr(void)
{
    struct rrdeng_page_descr *descr;

    descr = mallocz(sizeof(*descr));
    descr->page_length = 0;
    descr->start_time = INVALID_TIME;
    descr->end_time = INVALID_TIME;
    descr->id = NULL;
    descr->extent = NULL;
    descr->pg_cache_descr_state = 0;
    descr->pg_cache_descr = NULL;

    return descr;
}