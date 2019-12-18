#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_6__ {size_t name; scalar_t__ update_every; scalar_t__ entries; } ;
typedef  TYPE_1__ RRDSET ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,size_t) ; 
 scalar_t__ rrdset_first_entry_t (TYPE_1__*) ; 
 scalar_t__ rrdset_last_entry_t (TYPE_1__*) ; 
 size_t rrdset_last_slot (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline time_t rrdset_slot2time(RRDSET *st, size_t slot) {
    time_t ret;

    if(slot >= (size_t)st->entries) {
        error("INTERNAL ERROR: caller of rrdset_slot2time() gives invalid slot %zu", slot);
        slot = (size_t)st->entries - 1;
    }

    if(slot > rrdset_last_slot(st)) {
        ret = rrdset_last_entry_t(st) - (size_t)st->update_every * (rrdset_last_slot(st) - slot + (size_t)st->entries);
    }
    else {
        ret = rrdset_last_entry_t(st) - (size_t)st->update_every;
    }

    if(unlikely(ret < rrdset_first_entry_t(st))) {
        error("INTERNAL ERROR: rrdset_slot2time() on %s returns time too far in the past", st->name);
        ret = rrdset_first_entry_t(st);
    }

    if(unlikely(ret > rrdset_last_entry_t(st))) {
        error("INTERNAL ERROR: rrdset_slot2time() on %s returns time into the future", st->name);
        ret = rrdset_last_entry_t(st);
    }

    return ret;
}