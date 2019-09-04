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
struct logger_stats {scalar_t__ watcher_sent; scalar_t__ watcher_skipped; scalar_t__ worker_written; scalar_t__ worker_dropped; } ;
struct TYPE_2__ {int /*<<< orphan*/  log_watcher_sent; int /*<<< orphan*/  log_watcher_skipped; int /*<<< orphan*/  log_worker_written; int /*<<< orphan*/  log_worker_dropped; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 TYPE_1__ stats ; 

__attribute__((used)) static void logger_thread_sum_stats(struct logger_stats *ls) {
    STATS_LOCK();
    stats.log_worker_dropped  += ls->worker_dropped;
    stats.log_worker_written  += ls->worker_written;
    stats.log_watcher_skipped += ls->watcher_skipped;
    stats.log_watcher_sent    += ls->watcher_sent;
    STATS_UNLOCK();
}