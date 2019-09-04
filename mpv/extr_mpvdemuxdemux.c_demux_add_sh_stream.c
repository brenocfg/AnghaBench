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
struct sh_stream {int dummy; } ;
struct demuxer {struct demux_internal* in; } ;
struct demux_internal {int /*<<< orphan*/  lock; struct demuxer* d_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  demux_add_sh_stream_locked (struct demux_internal*,struct sh_stream*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void demux_add_sh_stream(struct demuxer *demuxer, struct sh_stream *sh)
{
    struct demux_internal *in = demuxer->in;
    assert(demuxer == in->d_thread);
    pthread_mutex_lock(&in->lock);
    demux_add_sh_stream_locked(in, sh);
    pthread_mutex_unlock(&in->lock);
}