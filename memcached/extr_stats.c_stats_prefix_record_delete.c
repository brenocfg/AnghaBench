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
struct TYPE_3__ {int /*<<< orphan*/  num_deletes; } ;
typedef  TYPE_1__ PREFIX_STATS ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 TYPE_1__* stats_prefix_find (char const*,size_t const) ; 

void stats_prefix_record_delete(const char *key, const size_t nkey) {
    PREFIX_STATS *pfs;

    STATS_LOCK();
    pfs = stats_prefix_find(key, nkey);
    if (NULL != pfs) {
        pfs->num_deletes++;
    }
    STATS_UNLOCK();
}