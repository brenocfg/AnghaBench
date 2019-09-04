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
struct TYPE_2__ {scalar_t__ web_usec_max; int /*<<< orphan*/  compressed_content_size; int /*<<< orphan*/  content_size; int /*<<< orphan*/  bytes_sent; int /*<<< orphan*/  bytes_received; int /*<<< orphan*/  web_usec; int /*<<< orphan*/  web_requests; } ;

/* Variables and functions */
 TYPE_1__ global_statistics ; 
 int /*<<< orphan*/  global_statistics_lock () ; 
 int /*<<< orphan*/  global_statistics_unlock () ; 
 scalar_t__ web_server_is_multithreaded ; 

void finished_web_request_statistics(uint64_t dt,
                                     uint64_t bytes_received,
                                     uint64_t bytes_sent,
                                     uint64_t content_size,
                                     uint64_t compressed_content_size) {
#if defined(HAVE_C___ATOMIC) && !defined(NETDATA_NO_ATOMIC_INSTRUCTIONS)
    uint64_t old_web_usec_max = global_statistics.web_usec_max;
    while(dt > old_web_usec_max)
        __atomic_compare_exchange(&global_statistics.web_usec_max, &old_web_usec_max, &dt, 1, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);

    __atomic_fetch_add(&global_statistics.web_requests, 1, __ATOMIC_SEQ_CST);
    __atomic_fetch_add(&global_statistics.web_usec, dt, __ATOMIC_SEQ_CST);
    __atomic_fetch_add(&global_statistics.bytes_received, bytes_received, __ATOMIC_SEQ_CST);
    __atomic_fetch_add(&global_statistics.bytes_sent, bytes_sent, __ATOMIC_SEQ_CST);
    __atomic_fetch_add(&global_statistics.content_size, content_size, __ATOMIC_SEQ_CST);
    __atomic_fetch_add(&global_statistics.compressed_content_size, compressed_content_size, __ATOMIC_SEQ_CST);
#else
#warning NOT using atomic operations - using locks for global statistics
    if (web_server_is_multithreaded)
        global_statistics_lock();

    if (dt > global_statistics.web_usec_max)
        global_statistics.web_usec_max = dt;

    global_statistics.web_requests++;
    global_statistics.web_usec += dt;
    global_statistics.bytes_received += bytes_received;
    global_statistics.bytes_sent += bytes_sent;
    global_statistics.content_size += content_size;
    global_statistics.compressed_content_size += compressed_content_size;

    if (web_server_is_multithreaded)
        global_statistics_unlock();
#endif
}