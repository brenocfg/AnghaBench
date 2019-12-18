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
struct statsd_udp {size_t size; struct statsd_udp* msgs; struct statsd_udp* iovecs; struct statsd_udp* iov_base; scalar_t__* running; } ;

/* Variables and functions */
 int /*<<< orphan*/  freez (struct statsd_udp*) ; 
 int /*<<< orphan*/  info (char*) ; 

void statsd_collector_thread_cleanup(void *data) {
    struct statsd_udp *d = data;
    *d->running = 0;

    info("cleaning up...");

#ifdef HAVE_RECVMMSG
    size_t i;
    for (i = 0; i < d->size; i++)
        freez(d->iovecs[i].iov_base);

    freez(d->iovecs);
    freez(d->msgs);
#endif

    freez(d);
}