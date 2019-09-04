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
struct demux_internal {int num_streams; int /*<<< orphan*/  lock; struct sh_stream** streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

struct sh_stream *demux_get_stream(struct demuxer *demuxer, int index)
{
    struct demux_internal *in = demuxer->in;
    pthread_mutex_lock(&in->lock);
    assert(index >= 0 && index < in->num_streams);
    struct sh_stream *r = in->streams[index];
    pthread_mutex_unlock(&in->lock);
    return r;
}