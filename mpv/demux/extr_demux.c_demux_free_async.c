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
struct demuxer {struct demux_internal* in; } ;
struct demux_internal {int thread_terminate; int shutdown_async; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  threading; struct demuxer* d_user; } ;
struct demux_free_async_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

struct demux_free_async_state *demux_free_async(struct demuxer *demuxer)
{
    struct demux_internal *in = demuxer->in;
    assert(demuxer == in->d_user);

    if (!in->threading)
        return NULL;

    pthread_mutex_lock(&in->lock);
    in->thread_terminate = true;
    in->shutdown_async = true;
    pthread_cond_signal(&in->wakeup);
    pthread_mutex_unlock(&in->lock);

    return (struct demux_free_async_state *)demuxer->in; // lies
}