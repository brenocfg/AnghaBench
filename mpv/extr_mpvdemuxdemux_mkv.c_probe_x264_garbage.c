#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct sh_stream {scalar_t__ type; TYPE_2__* codec; } ;
struct block_info {int num_laces; TYPE_1__** laces; TYPE_3__* track; } ;
struct TYPE_15__ {struct sh_stream* stream; } ;
typedef  TYPE_3__ mkv_track_t ;
struct TYPE_16__ {int num_tracks; int num_blocks; struct block_info* blocks; TYPE_3__** tracks; } ;
typedef  TYPE_4__ mkv_demuxer_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; TYPE_4__* priv; } ;
typedef  TYPE_5__ demuxer_t ;
struct TYPE_18__ {scalar_t__ start; int /*<<< orphan*/  len; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ bstr ;
struct TYPE_14__ {int /*<<< orphan*/  first_packet; scalar_t__ codec; } ;
struct TYPE_13__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ STREAM_VIDEO ; 
 TYPE_6__ demux_mkv_decode (int /*<<< orphan*/ ,TYPE_3__*,TYPE_6__,int) ; 
 int /*<<< orphan*/  new_demux_packet_from (scalar_t__,int /*<<< orphan*/ ) ; 
 int read_next_block_into_queue (TYPE_5__*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  talloc_free (scalar_t__) ; 
 int /*<<< orphan*/  talloc_steal (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void probe_x264_garbage(demuxer_t *demuxer)
{
    mkv_demuxer_t *mkv_d = demuxer->priv;

    for (int n = 0; n < mkv_d->num_tracks; n++) {
        mkv_track_t *track = mkv_d->tracks[n];
        struct sh_stream *sh = track->stream;

        if (!sh || sh->type != STREAM_VIDEO)
            continue;

        if (sh->codec->codec && strcmp(sh->codec->codec, "h264") != 0)
            continue;

        struct block_info *block = NULL;

        // Find first block for this track.
        // Restrict reading number of total packets. (Arbitrary to avoid bloat.)
        for (int i = 0; i < 100; i++) {
            if (i >= mkv_d->num_blocks && read_next_block_into_queue(demuxer) < 1)
                break;
            if (mkv_d->blocks[i].track == track) {
                block = &mkv_d->blocks[i];
                break;
            }
        }

        if (!block || block->num_laces < 1)
            continue;

        bstr sblock = {block->laces[0]->data, block->laces[0]->size};
        bstr nblock = demux_mkv_decode(demuxer->log, track, sblock, 1);

        sh->codec->first_packet = new_demux_packet_from(nblock.start, nblock.len);
        talloc_steal(mkv_d, sh->codec->first_packet);

        if (nblock.start != sblock.start)
            talloc_free(nblock.start);
    }
}