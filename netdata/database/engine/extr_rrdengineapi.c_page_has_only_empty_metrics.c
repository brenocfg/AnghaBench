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
typedef  int uint8_t ;
struct rrdeng_page_descr {int page_length; TYPE_1__* pg_cache_descr; } ;
typedef  scalar_t__ storage_number ;
struct TYPE_2__ {scalar_t__* page; } ;

/* Variables and functions */
 scalar_t__ SN_EMPTY_SLOT ; 

__attribute__((used)) static int page_has_only_empty_metrics(struct rrdeng_page_descr *descr)
{
    unsigned i;
    uint8_t has_only_empty_metrics = 1;
    storage_number *page;

    page = descr->pg_cache_descr->page;
    for (i = 0 ; i < descr->page_length / sizeof(storage_number); ++i) {
        if (SN_EMPTY_SLOT != page[i]) {
            has_only_empty_metrics = 0;
            break;
        }
    }
    return has_only_empty_metrics;
}