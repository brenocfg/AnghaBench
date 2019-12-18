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
struct timespec {int dummy; } ;
struct demux_internal {int shutdown_async; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup_cb_ctx; int /*<<< orphan*/  (* wakeup_cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  wakeup; int /*<<< orphan*/  next_cache_update; int /*<<< orphan*/  thread_terminate; } ;

/* Variables and functions */
 int /*<<< orphan*/  demux_shutdown (struct demux_internal*) ; 
 struct timespec mp_time_us_to_timespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpthread_set_name (char*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_work (struct demux_internal*) ; 

__attribute__((used)) static void *demux_thread(void *pctx)
{
    struct demux_internal *in = pctx;
    mpthread_set_name("demux");
    pthread_mutex_lock(&in->lock);

    while (!in->thread_terminate) {
        if (thread_work(in))
            continue;
        pthread_cond_signal(&in->wakeup);
        struct timespec until = mp_time_us_to_timespec(in->next_cache_update);
        pthread_cond_timedwait(&in->wakeup, &in->lock, &until);
    }

    if (in->shutdown_async) {
        pthread_mutex_unlock(&in->lock);
        demux_shutdown(in);
        pthread_mutex_lock(&in->lock);
        in->shutdown_async = false;
        if (in->wakeup_cb)
            in->wakeup_cb(in->wakeup_cb_ctx);
    }

    pthread_mutex_unlock(&in->lock);
    return NULL;
}