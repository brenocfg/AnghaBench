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
struct demux_internal {int num_streams; int reading; int /*<<< orphan*/  lock; TYPE_1__** streams; int /*<<< orphan*/  blocked; int /*<<< orphan*/  threading; } ;
struct TYPE_2__ {int /*<<< orphan*/  ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int dequeue_packet (int /*<<< orphan*/ ,struct demux_packet**) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int thread_work (struct demux_internal*) ; 

struct demux_packet *demux_read_any_packet(struct demuxer *demuxer)
{
    struct demux_internal *in = demuxer->in;
    pthread_mutex_lock(&in->lock);
    assert(!in->threading); // doesn't work with threading
    struct demux_packet *out_pkt = NULL;
    bool read_more = true;
    while (read_more && !in->blocked) {
        bool all_eof = true;
        for (int n = 0; n < in->num_streams; n++) {
            in->reading = true; // force read_packet() to read
            int r = dequeue_packet(in->streams[n]->ds, &out_pkt);
            if (r > 0)
                goto done;
            if (r == 0)
                all_eof = false;
        }
        // retry after calling this
        read_more = thread_work(in);
        read_more &= !all_eof;
    }
done:
    pthread_mutex_unlock(&in->lock);
    return out_pkt;
}