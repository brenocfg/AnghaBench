#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_stream {int /*<<< orphan*/  index; } ;
struct demuxer {TYPE_1__* priv; } ;
struct demux_packet {int /*<<< orphan*/  stream; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_packets; int /*<<< orphan*/  packets; } ;
typedef  TYPE_1__ mkv_demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct demux_packet*) ; 

__attribute__((used)) static void add_packet(struct demuxer *demuxer, struct sh_stream *stream,
                       struct demux_packet *pkt)
{
    mkv_demuxer_t *mkv_d = demuxer->priv;
    if (!pkt)
        return;

    pkt->stream = stream->index;
    MP_TARRAY_APPEND(mkv_d, mkv_d->packets, mkv_d->num_packets, pkt);
}