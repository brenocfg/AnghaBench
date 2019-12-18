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
typedef  int /*<<< orphan*/  storage_number ;
typedef  scalar_t__ RRD_MEMORY_MODE ;
typedef  int /*<<< orphan*/  RRDDIM ;

/* Variables and functions */
 long RRD_HISTORY_ENTRIES_MAX ; 
 scalar_t__ RRD_MEMORY_MODE_ALLOC ; 
 scalar_t__ RRD_MEMORY_MODE_NONE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (long) ; 

inline long align_entries_to_pagesize(RRD_MEMORY_MODE mode, long entries) {
    if(unlikely(entries < 5)) entries = 5;
    if(unlikely(entries > RRD_HISTORY_ENTRIES_MAX)) entries = RRD_HISTORY_ENTRIES_MAX;

    if(unlikely(mode == RRD_MEMORY_MODE_NONE || mode == RRD_MEMORY_MODE_ALLOC))
        return entries;

    long page = (size_t)sysconf(_SC_PAGESIZE);
    long size = sizeof(RRDDIM) + entries * sizeof(storage_number);
    if(unlikely(size % page)) {
        size -= (size % page);
        size += page;

        long n = (size - sizeof(RRDDIM)) / sizeof(storage_number);
        return n;
    }

    return entries;
}