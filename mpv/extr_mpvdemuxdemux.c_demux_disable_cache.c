#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct demux_internal {int seekable_cache; int /*<<< orphan*/  lock; TYPE_1__* d_user; } ;
struct TYPE_4__ {struct demux_internal* in; } ;
typedef  TYPE_1__ demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free_empty_cached_ranges (struct demux_internal*) ; 
 int /*<<< orphan*/  prune_old_packets (struct demux_internal*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void demux_disable_cache(demuxer_t *demuxer)
{
    struct demux_internal *in = demuxer->in;
    assert(demuxer == in->d_user);

    pthread_mutex_lock(&in->lock);
    if (in->seekable_cache) {
        MP_VERBOSE(demuxer, "disabling persistent packet cache\n");
        in->seekable_cache = false;

        // Get rid of potential buffered ranges floating around.
        free_empty_cached_ranges(in);
        // Get rid of potential old packets in the current range.
        prune_old_packets(in);
    }
    pthread_mutex_unlock(&in->lock);
}