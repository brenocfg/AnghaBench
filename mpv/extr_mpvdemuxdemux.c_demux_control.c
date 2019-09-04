#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct demux_internal {int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  (* run_fn ) (struct demux_control_args*) ;struct demux_control_args* run_fn_arg; scalar_t__ threading; TYPE_1__* d_user; } ;
struct demux_control_args {int member_1; void* member_2; int* member_3; TYPE_1__* member_0; } ;
struct TYPE_3__ {struct demux_internal* in; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int CONTROL_UNKNOWN ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demux_internal*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int cached_demux_control (struct demux_internal*,int,void*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_demux_control (struct demux_control_args*) ; 

int demux_control(demuxer_t *demuxer, int cmd, void *arg)
{
    struct demux_internal *in = demuxer->in;
    assert(demuxer == in->d_user);

    if (in->threading) {
        pthread_mutex_lock(&in->lock);
        int cr = cached_demux_control(in, cmd, arg);
        pthread_mutex_unlock(&in->lock);
        if (cr != CONTROL_UNKNOWN)
            return cr;
    }

    int r = 0;
    struct demux_control_args args = {demuxer, cmd, arg, &r};
    if (in->threading) {
        MP_VERBOSE(in, "blocking on demuxer thread\n");
        pthread_mutex_lock(&in->lock);
        while (in->run_fn)
            pthread_cond_wait(&in->wakeup, &in->lock);
        in->run_fn = thread_demux_control;
        in->run_fn_arg = &args;
        pthread_cond_signal(&in->wakeup);
        while (in->run_fn)
            pthread_cond_wait(&in->wakeup, &in->lock);
        pthread_mutex_unlock(&in->lock);
    } else {
        pthread_mutex_lock(&in->lock);
        thread_demux_control(&args);
        pthread_mutex_unlock(&in->lock);
    }

    return r;
}