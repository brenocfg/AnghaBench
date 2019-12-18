#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t counter; scalar_t__ current_entry; scalar_t__ entries; } ;
typedef  TYPE_1__ RRDSET ;

/* Variables and functions */

__attribute__((used)) static inline size_t rrdset_first_slot(RRDSET *st) {
    if(st->counter >= (size_t)st->entries) {
        // the database has been rotated at least once
        // the oldest entry is the one that will be next
        // overwritten by data collection
        return (size_t)st->current_entry;
    }

    // we do not have rotated the db yet
    // so 0 is the first entry
    return 0;
}