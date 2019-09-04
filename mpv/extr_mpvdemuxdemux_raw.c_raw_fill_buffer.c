#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct priv {int frame_size; int read_frames; int frame_rate; int /*<<< orphan*/  sh; } ;
struct demux_packet {int pos; int pts; int /*<<< orphan*/  len; int /*<<< orphan*/  buffer; } ;
struct TYPE_6__ {TYPE_2__* stream; struct priv* priv; } ;
typedef  TYPE_1__ demuxer_t ;
struct TYPE_7__ {scalar_t__ eof; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  demux_add_packet (int /*<<< orphan*/ ,struct demux_packet*) ; 
 int /*<<< orphan*/  demux_packet_shorten (struct demux_packet*,int) ; 
 struct demux_packet* new_demux_packet (int) ; 
 int stream_read (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stream_tell (TYPE_2__*) ; 

__attribute__((used)) static int raw_fill_buffer(demuxer_t *demuxer)
{
    struct priv *p = demuxer->priv;

    if (demuxer->stream->eof)
        return 0;

    struct demux_packet *dp = new_demux_packet(p->frame_size * p->read_frames);
    if (!dp) {
        MP_ERR(demuxer, "Can't read packet.\n");
        return 1;
    }

    dp->pos = stream_tell(demuxer->stream);
    dp->pts = (dp->pos  / p->frame_size) / p->frame_rate;

    int len = stream_read(demuxer->stream, dp->buffer, dp->len);
    demux_packet_shorten(dp, len);
    demux_add_packet(p->sh, dp);

    return 1;
}