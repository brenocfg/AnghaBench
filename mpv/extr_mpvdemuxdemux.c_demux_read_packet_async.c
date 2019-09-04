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
struct sh_stream {struct demux_stream* ds; } ;
struct demux_stream {int need_wakeup; TYPE_1__* in; scalar_t__ eof; scalar_t__ eager; } ;
struct demux_packet {int dummy; } ;
struct TYPE_2__ {int reading; int eof; scalar_t__ blocked; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; scalar_t__ threading; } ;

/* Variables and functions */
 struct demux_packet* demux_read_packet (struct sh_stream*) ; 
 struct demux_packet* dequeue_packet (struct demux_stream*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int demux_read_packet_async(struct sh_stream *sh, struct demux_packet **out_pkt)
{
    struct demux_stream *ds = sh ? sh->ds : NULL;
    int r = -1;
    *out_pkt = NULL;
    if (!ds)
        return r;
    if (ds->in->threading) {
        pthread_mutex_lock(&ds->in->lock);
        *out_pkt = dequeue_packet(ds);
        if (ds->eager) {
            r = *out_pkt ? 1 : (ds->eof ? -1 : 0);
            ds->in->reading = true; // enable readahead
            ds->in->eof = false; // force retry
            pthread_cond_signal(&ds->in->wakeup); // possibly read more
        } else {
            r = *out_pkt ? 1 : -1;
        }
        ds->need_wakeup = r != 1;
        pthread_mutex_unlock(&ds->in->lock);
    } else {
        if (ds->in->blocked) {
            r = 0;
        } else {
            *out_pkt = demux_read_packet(sh);
            r = *out_pkt ? 1 : -1;
        }
        ds->need_wakeup = r != 1;
    }
    return r;
}