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
struct demux_internal {int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; int /*<<< orphan*/  ts_offset; TYPE_1__* d_user; } ;
struct TYPE_3__ {struct demux_internal* in; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 double MP_ADD_PTS (double,int /*<<< orphan*/ ) ; 
 int SEEK_FACTOR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int queue_seek (struct demux_internal*,double,int,int) ; 

int demux_seek(demuxer_t *demuxer, double seek_pts, int flags)
{
    struct demux_internal *in = demuxer->in;
    assert(demuxer == in->d_user);

    pthread_mutex_lock(&in->lock);

    if (!(flags & SEEK_FACTOR))
        seek_pts = MP_ADD_PTS(seek_pts, -in->ts_offset);

    int res = queue_seek(in, seek_pts, flags, true);

    pthread_cond_signal(&in->wakeup);
    pthread_mutex_unlock(&in->lock);

    return res;
}