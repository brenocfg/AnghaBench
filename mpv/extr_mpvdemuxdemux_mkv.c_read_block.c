#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
struct block_info {int filepos; int keyframe; TYPE_1__* track; scalar_t__ timecode; scalar_t__ simple; } ;
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_6__ {int tc_scale; int num_tracks; TYPE_1__** tracks; scalar_t__ cluster_tc; } ;
typedef  TYPE_2__ mkv_demuxer_t ;
typedef  scalar_t__ int64_t ;
typedef  int int16_t ;
struct TYPE_7__ {int /*<<< orphan*/ * stream; scalar_t__ priv; } ;
typedef  TYPE_3__ demuxer_t ;
struct TYPE_5__ {int tnum; } ;

/* Variables and functions */
 int EBML_UINT_INVALID ; 
 scalar_t__ demux_mkv_read_block_lacing (struct block_info*,int,int /*<<< orphan*/ *,int) ; 
 int ebml_read_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_block (struct block_info*) ; 
 int stream_read_char (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_seek (int /*<<< orphan*/ *,int) ; 
 int stream_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_block(demuxer_t *demuxer, int64_t end, struct block_info *block)
{
    mkv_demuxer_t *mkv_d = (mkv_demuxer_t *) demuxer->priv;
    stream_t *s = demuxer->stream;
    uint64_t num;
    int16_t time;
    uint64_t length;

    free_block(block);
    length = ebml_read_length(s);
    if (!length || length > 500000000 || stream_tell(s) + length > (uint64_t)end)
        return -1;

    uint64_t endpos = stream_tell(s) + length;
    int res = -1;

    // Parse header of the Block element
    /* first byte(s): track num */
    num = ebml_read_length(s);
    if (num == EBML_UINT_INVALID || stream_tell(s) >= endpos)
        goto exit;

    /* time (relative to cluster time) */
    if (stream_tell(s) + 3 > endpos)
        goto exit;
    uint8_t c1 = stream_read_char(s);
    uint8_t c2 = stream_read_char(s);
    time = c1 << 8 | c2;

    uint8_t header_flags = stream_read_char(s);

    block->filepos = stream_tell(s);

    int lace_type = (header_flags >> 1) & 0x03;
    if (demux_mkv_read_block_lacing(block, lace_type, s, endpos))
        goto exit;

    if (block->simple)
        block->keyframe = header_flags & 0x80;
    block->timecode = time * mkv_d->tc_scale + mkv_d->cluster_tc;
    for (int i = 0; i < mkv_d->num_tracks; i++) {
        if (mkv_d->tracks[i]->tnum == num) {
            block->track = mkv_d->tracks[i];
            break;
        }
    }
    if (!block->track) {
        res = 0;
        goto exit;
    }

    if (stream_tell(s) != endpos)
        goto exit;

    res = 1;
exit:
    if (res <= 0)
        free_block(block);
    stream_seek(s, endpos);
    return res;
}