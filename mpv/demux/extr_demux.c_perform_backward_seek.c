#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct demux_stream {int back_resuming; int /*<<< orphan*/  back_seek_pos; TYPE_2__* reader_head; int /*<<< orphan*/  back_resume_dts; int /*<<< orphan*/  back_resume_pos; scalar_t__ eager; int /*<<< orphan*/  back_restarting; } ;
struct demux_internal {int num_streams; int reading; int /*<<< orphan*/  lock; TYPE_3__* d_thread; TYPE_1__** streams; } ;
struct TYPE_6__ {int /*<<< orphan*/  start_time; } ;
struct TYPE_5__ {int /*<<< orphan*/  dts; int /*<<< orphan*/  pos; } ;
struct TYPE_4__ {struct demux_stream* ds; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 double MP_PTS_MIN (double,int /*<<< orphan*/ ) ; 
 double MP_PTS_OR_DEF (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demux_internal*,char*) ; 
 int SEEK_HR ; 
 int SEEK_SATAN ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_seek (struct demux_internal*,double,int,int) ; 

__attribute__((used)) static void perform_backward_seek(struct demux_internal *in)
{
    double target = MP_NOPTS_VALUE;

    for (int n = 0; n < in->num_streams; n++) {
        struct demux_stream *ds = in->streams[n]->ds;

        if (ds->reader_head && !ds->back_restarting && !ds->back_resuming &&
            ds->eager)
        {
            ds->back_resuming = true;
            ds->back_resume_pos = ds->reader_head->pos;
            ds->back_resume_dts = ds->reader_head->dts;
        }

        target = MP_PTS_MIN(target, ds->back_seek_pos);
    }

    target = MP_PTS_OR_DEF(target, in->d_thread->start_time);

    MP_VERBOSE(in, "triggering backward seek to get more packets\n");
    queue_seek(in, target, SEEK_SATAN | SEEK_HR, false);
    in->reading = true;

    // Don't starve other threads.
    pthread_mutex_unlock(&in->lock);
    pthread_mutex_lock(&in->lock);
}