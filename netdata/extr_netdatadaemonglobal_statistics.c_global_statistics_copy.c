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
struct global_statistics {int dummy; } ;
struct TYPE_2__ {scalar_t__ web_usec_max; } ;

/* Variables and functions */
 int GLOBAL_STATS_RESET_WEB_USEC_MAX ; 
 TYPE_1__ global_statistics ; 
 int /*<<< orphan*/  global_statistics_lock () ; 
 int /*<<< orphan*/  global_statistics_unlock () ; 
 int /*<<< orphan*/  memcpy (struct global_statistics*,void const*,int) ; 

__attribute__((used)) static inline void global_statistics_copy(struct global_statistics *gs, uint8_t options) {
#if defined(HAVE_C___ATOMIC) && !defined(NETDATA_NO_ATOMIC_INSTRUCTIONS)
    gs->connected_clients            = __atomic_fetch_add(&global_statistics.connected_clients, 0, __ATOMIC_SEQ_CST);
    gs->web_requests                 = __atomic_fetch_add(&global_statistics.web_requests, 0, __ATOMIC_SEQ_CST);
    gs->web_usec                     = __atomic_fetch_add(&global_statistics.web_usec, 0, __ATOMIC_SEQ_CST);
    gs->web_usec_max                 = __atomic_fetch_add(&global_statistics.web_usec_max, 0, __ATOMIC_SEQ_CST);
    gs->bytes_received               = __atomic_fetch_add(&global_statistics.bytes_received, 0, __ATOMIC_SEQ_CST);
    gs->bytes_sent                   = __atomic_fetch_add(&global_statistics.bytes_sent, 0, __ATOMIC_SEQ_CST);
    gs->content_size                 = __atomic_fetch_add(&global_statistics.content_size, 0, __ATOMIC_SEQ_CST);
    gs->compressed_content_size      = __atomic_fetch_add(&global_statistics.compressed_content_size, 0, __ATOMIC_SEQ_CST);
    gs->web_client_count             = __atomic_fetch_add(&global_statistics.web_client_count, 0, __ATOMIC_SEQ_CST);

    gs->rrdr_queries_made            = __atomic_fetch_add(&global_statistics.rrdr_queries_made, 0, __ATOMIC_SEQ_CST);
    gs->rrdr_db_points_read          = __atomic_fetch_add(&global_statistics.rrdr_db_points_read, 0, __ATOMIC_SEQ_CST);
    gs->rrdr_result_points_generated = __atomic_fetch_add(&global_statistics.rrdr_result_points_generated, 0, __ATOMIC_SEQ_CST);

    if(options & GLOBAL_STATS_RESET_WEB_USEC_MAX) {
        uint64_t n = 0;
        __atomic_compare_exchange(&global_statistics.web_usec_max, &gs->web_usec_max, &n, 1, __ATOMIC_SEQ_CST,
                                  __ATOMIC_SEQ_CST);
    }
#else
    global_statistics_lock();

    memcpy(gs, (const void *)&global_statistics, sizeof(struct global_statistics));

    if (options & GLOBAL_STATS_RESET_WEB_USEC_MAX)
        global_statistics.web_usec_max = 0;

    global_statistics_unlock();
#endif
}