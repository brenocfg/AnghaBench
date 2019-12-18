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
struct demux_internal {int num_ranges; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ranges; TYPE_1__* d_user; } ;
struct TYPE_3__ {struct demux_internal* in; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_cached_range (struct demux_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_reader_state (struct demux_internal*,int) ; 
 int /*<<< orphan*/  free_empty_cached_ranges (struct demux_internal*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void demux_flush(demuxer_t *demuxer)
{
    struct demux_internal *in = demuxer->in;
    assert(demuxer == in->d_user);

    pthread_mutex_lock(&demuxer->in->lock);
    clear_reader_state(in, true);
    for (int n = 0; n < in->num_ranges; n++)
        clear_cached_range(in, in->ranges[n]);
    free_empty_cached_ranges(in);
    pthread_mutex_unlock(&demuxer->in->lock);
}