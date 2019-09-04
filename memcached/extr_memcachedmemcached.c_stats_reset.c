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
struct stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 int /*<<< orphan*/  item_stats_reset () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stats ; 
 int /*<<< orphan*/  stats_prefix_clear () ; 
 int /*<<< orphan*/  threadlocal_stats_reset () ; 

__attribute__((used)) static void stats_reset(void) {
    STATS_LOCK();
    memset(&stats, 0, sizeof(struct stats));
    stats_prefix_clear();
    STATS_UNLOCK();
    threadlocal_stats_reset();
    item_stats_reset();
}