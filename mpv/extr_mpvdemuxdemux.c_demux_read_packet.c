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
struct sh_stream {struct demux_stream* ds; } ;
struct demux_stream {int need_wakeup; scalar_t__ eof; int /*<<< orphan*/  reader_head; scalar_t__ selected; int /*<<< orphan*/  type; scalar_t__ eager; struct demux_internal* in; } ;
struct demux_packet {int dummy; } ;
struct demux_internal {int eof; int reading; int /*<<< orphan*/  lock; int /*<<< orphan*/  wakeup; scalar_t__ threading; int /*<<< orphan*/  blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_DBG (struct demux_internal*,char*,char const*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demux_internal*,char*,char const*) ; 
 struct demux_packet* dequeue_packet (struct demux_stream*) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 char* stream_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_work (struct demux_internal*) ; 

struct demux_packet *demux_read_packet(struct sh_stream *sh)
{
    struct demux_stream *ds = sh ? sh->ds : NULL;
    if (!ds)
        return NULL;
    struct demux_internal *in = ds->in;
    pthread_mutex_lock(&in->lock);
    if (ds->eager) {
        const char *t = stream_type_name(ds->type);
        MP_DBG(in, "reading packet for %s\n", t);
        in->eof = false; // force retry
        ds->need_wakeup = true;
        while (ds->selected && !ds->reader_head && !in->blocked) {
            in->reading = true;
            // Note: the following code marks EOF if it can't continue
            if (in->threading) {
                MP_VERBOSE(in, "waiting for demux thread (%s)\n", t);
                pthread_cond_signal(&in->wakeup);
                pthread_cond_wait(&in->wakeup, &in->lock);
            } else {
                thread_work(in);
            }
            if (ds->eof)
                break;
        }
    }
    struct demux_packet *pkt = dequeue_packet(ds);
    pthread_cond_signal(&in->wakeup); // possibly read more
    pthread_mutex_unlock(&in->lock);
    return pkt;
}