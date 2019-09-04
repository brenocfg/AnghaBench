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
struct TYPE_2__ {scalar_t__ size; } ;
struct mp_decode {int packet_pending; TYPE_1__ packets; int /*<<< orphan*/  orig_pkt; } ;
typedef  int /*<<< orphan*/  pkt ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  circlebuf_pop_front (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void mp_decode_clear_packets(struct mp_decode *d)
{
	if (d->packet_pending) {
		av_packet_unref(&d->orig_pkt);
		d->packet_pending = false;
	}

	while (d->packets.size) {
		AVPacket pkt;
		circlebuf_pop_front(&d->packets, &pkt, sizeof(pkt));
		av_packet_unref(&pkt);
	}
}