#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct demux_packet {int dummy; } ;
struct dec_sub {int preload_attempted; int /*<<< orphan*/  lock; TYPE_2__* sd; int /*<<< orphan*/  demux_waiter; int /*<<< orphan*/  sh; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* decode ) (TYPE_2__*,struct demux_packet*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITY ; 
 int demux_read_packet_async (int /*<<< orphan*/ ,struct demux_packet**) ; 
 int /*<<< orphan*/  mp_dispatch_queue_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct demux_packet*) ; 
 int /*<<< orphan*/  talloc_free (struct demux_packet*) ; 

void sub_preload(struct dec_sub *sub)
{
    pthread_mutex_lock(&sub->lock);

    sub->preload_attempted = true;

    for (;;) {
        struct demux_packet *pkt = NULL;
        int r = demux_read_packet_async(sub->sh, &pkt);
        if (r == 0) {
            mp_dispatch_queue_process(sub->demux_waiter, INFINITY);
            continue;
        }
        if (!pkt)
            break;
        sub->sd->driver->decode(sub->sd, pkt);
        talloc_free(pkt);
    }

    pthread_mutex_unlock(&sub->lock);
}