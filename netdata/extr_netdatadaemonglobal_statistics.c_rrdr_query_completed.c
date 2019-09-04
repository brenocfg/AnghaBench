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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  rrdr_result_points_generated; int /*<<< orphan*/  rrdr_db_points_read; int /*<<< orphan*/  rrdr_queries_made; } ;

/* Variables and functions */
 TYPE_1__ global_statistics ; 
 int /*<<< orphan*/  global_statistics_lock () ; 
 int /*<<< orphan*/  global_statistics_unlock () ; 
 scalar_t__ web_server_is_multithreaded ; 

void rrdr_query_completed(uint64_t db_points_read, uint64_t result_points_generated) {
#if defined(HAVE_C___ATOMIC) && !defined(NETDATA_NO_ATOMIC_INSTRUCTIONS)
    __atomic_fetch_add(&global_statistics.rrdr_queries_made, 1, __ATOMIC_SEQ_CST);
    __atomic_fetch_add(&global_statistics.rrdr_db_points_read, db_points_read, __ATOMIC_SEQ_CST);
    __atomic_fetch_add(&global_statistics.rrdr_result_points_generated, result_points_generated, __ATOMIC_SEQ_CST);
#else
    #warning NOT using atomic operations - using locks for global statistics
    if (web_server_is_multithreaded)
        global_statistics_lock();

    global_statistics.rrdr_queries_made++;
    global_statistics.rrdr_db_points_read += db_points_read;
    global_statistics.rrdr_result_points_generated += result_points_generated;

    if (web_server_is_multithreaded)
        global_statistics_unlock();
#endif
}