#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ netdata_thread_t ;
struct TYPE_7__ {int rrdpush_sender_join; scalar_t__ rrdpush_sender_thread; int /*<<< orphan*/  hostname; scalar_t__ rrdpush_sender_spawn; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdata_thread_cancel (scalar_t__) ; 
 int /*<<< orphan*/  netdata_thread_join (scalar_t__,void**) ; 
 int /*<<< orphan*/  rrdhost_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdhost_wrlock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdpush_buffer_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  rrdpush_buffer_unlock (TYPE_1__*) ; 

void rrdpush_sender_thread_stop(RRDHOST *host) {
    rrdpush_buffer_lock(host);
    rrdhost_wrlock(host);

    netdata_thread_t thr = 0;

    if(host->rrdpush_sender_spawn) {
        info("STREAM %s [send]: signaling sending thread to stop...", host->hostname);

        // signal the thread that we want to join it
        host->rrdpush_sender_join = 1;

        // copy the thread id, so that we will be waiting for the right one
        // even if a new one has been spawn
        thr = host->rrdpush_sender_thread;

        // signal it to cancel
        netdata_thread_cancel(host->rrdpush_sender_thread);
    }

    rrdhost_unlock(host);
    rrdpush_buffer_unlock(host);

    if(thr != 0) {
        info("STREAM %s [send]: waiting for the sending thread to stop...", host->hostname);
        void *result;
        netdata_thread_join(thr, &result);
        info("STREAM %s [send]: sending thread has exited.", host->hostname);
    }
}