#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct priv {int frame_size; int read_frames; int frame_rate; TYPE_1__* sh; } ;
struct demuxer {TYPE_2__* stream; struct priv* priv; } ;
struct demux_packet {int keyframe; int pos; int pts; int /*<<< orphan*/  stream; int /*<<< orphan*/  len; int /*<<< orphan*/  buffer; } ;
struct TYPE_5__ {scalar_t__ eof; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct demuxer*,char*) ; 
 int /*<<< orphan*/  demux_packet_shorten (struct demux_packet*,int) ; 
 struct demux_packet* new_demux_packet (int) ; 
 int stream_read (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stream_tell (TYPE_2__*) ; 

__attribute__((used)) static bool raw_read_packet(struct demuxer *demuxer, struct demux_packet **pkt)
{
    struct priv *p = demuxer->priv;

    if (demuxer->stream->eof)
        return false;

    struct demux_packet *dp = new_demux_packet(p->frame_size * p->read_frames);
    if (!dp) {
        MP_ERR(demuxer, "Can't read packet.\n");
        return true;
    }

    dp->keyframe = true;
    dp->pos = stream_tell(demuxer->stream);
    dp->pts = (dp->pos  / p->frame_size) / p->frame_rate;

    int len = stream_read(demuxer->stream, dp->buffer, dp->len);
    demux_packet_shorten(dp, len);

    dp->stream = p->sh->index;
    *pkt = dp;

    return true;
}