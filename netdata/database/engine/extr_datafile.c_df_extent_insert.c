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
struct TYPE_2__ {struct extent_info* last; struct extent_info* first; } ;
struct rrdengine_datafile {TYPE_1__ extents; } ;
struct extent_info {struct extent_info* next; struct rrdengine_datafile* datafile; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

void df_extent_insert(struct extent_info *extent)
{
    struct rrdengine_datafile *datafile = extent->datafile;

    if (likely(NULL != datafile->extents.last)) {
        datafile->extents.last->next = extent;
    }
    if (unlikely(NULL == datafile->extents.first)) {
        datafile->extents.first = extent;
    }
    datafile->extents.last = extent;
}