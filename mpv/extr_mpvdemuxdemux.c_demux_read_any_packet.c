#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct demuxer {struct demux_internal* in; } ;
struct demux_packet {int dummy; } ;
struct demux_internal {int num_streams; int reading; int /*<<< orphan*/  lock; int /*<<< orphan*/  eof; TYPE_1__** streams; int /*<<< orphan*/  blocked; int /*<<< orphan*/  threading; } ;
struct TYPE_2__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct demux_packet* dequeue_packet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int thread_work (struct demux_internal*) ; 

struct demux_packet *demux_read_any_packet(struct demuxer *demuxer)
{
    struct demux_internal *in = demuxer->in;
    assert(!in->threading); // doesn't work with threading
    bool read_more = true;
    while (read_more && !in->blocked) {
        for (int n = 0; n < in->num_streams; n++) {
            in->reading = true; // force read_packet() to read
            struct demux_packet *pkt = dequeue_packet(in->streams[n]->ds);
            if (pkt)
                return pkt;
        }
        // retry after calling this
        pthread_mutex_lock(&in->lock); // lock only because thread_work unlocks
        read_more = thread_work(in);
        read_more &= !in->eof;
        pthread_mutex_unlock(&in->lock);
    }
    return NULL;
}