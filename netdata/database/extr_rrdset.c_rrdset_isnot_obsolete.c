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
typedef  int /*<<< orphan*/  RRDSET ;

/* Variables and functions */
 int /*<<< orphan*/  RRDSET_FLAG_OBSOLETE ; 
 int /*<<< orphan*/  RRDSET_FLAG_UPSTREAM_EXPOSED ; 
 int /*<<< orphan*/  rrdset_flag_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdset_flag_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

inline void rrdset_isnot_obsolete(RRDSET *st) {
    if(unlikely((rrdset_flag_check(st, RRDSET_FLAG_OBSOLETE)))) {
        rrdset_flag_clear(st, RRDSET_FLAG_OBSOLETE);
        rrdset_flag_clear(st, RRDSET_FLAG_UPSTREAM_EXPOSED);

        // the chart will be pushed upstream automatically
        // due to data collection
    }
}