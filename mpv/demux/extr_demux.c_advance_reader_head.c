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
struct demux_stream {int /*<<< orphan*/  last_ret_dts; int /*<<< orphan*/  last_ret_pos; struct demux_packet* reader_head; } ;
struct demux_packet {int /*<<< orphan*/  dts; int /*<<< orphan*/  pos; struct demux_packet* next; } ;

/* Variables and functions */

__attribute__((used)) static struct demux_packet *advance_reader_head(struct demux_stream *ds)
{
    struct demux_packet *pkt = ds->reader_head;
    if (!pkt)
        return NULL;

    ds->reader_head = pkt->next;

    ds->last_ret_pos = pkt->pos;
    ds->last_ret_dts = pkt->dts;

    return pkt;
}