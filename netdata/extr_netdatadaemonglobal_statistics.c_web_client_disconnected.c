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
struct TYPE_2__ {int /*<<< orphan*/  connected_clients; } ;

/* Variables and functions */
 TYPE_1__ global_statistics ; 
 int /*<<< orphan*/  global_statistics_lock () ; 
 int /*<<< orphan*/  global_statistics_unlock () ; 
 scalar_t__ web_server_is_multithreaded ; 

void web_client_disconnected(void) {
#if defined(HAVE_C___ATOMIC) && !defined(NETDATA_NO_ATOMIC_INSTRUCTIONS)
    __atomic_fetch_sub(&global_statistics.connected_clients, 1, __ATOMIC_SEQ_CST);
#else
    if (web_server_is_multithreaded)
        global_statistics_lock();

    global_statistics.connected_clients--;

    if (web_server_is_multithreaded)
        global_statistics_unlock();
#endif
}