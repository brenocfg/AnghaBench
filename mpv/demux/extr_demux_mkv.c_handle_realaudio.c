#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct demux_packet {int* buffer; int len; scalar_t__ pts; scalar_t__ pos; } ;
struct TYPE_9__ {int sub_packet_size; int sub_packet_h; int coded_framesize; int audiopk_size; int sub_packet_cnt; int* audio_buf; scalar_t__* audio_timestamp; scalar_t__ ra_pts; TYPE_6__* stream; } ;
typedef  TYPE_2__ mkv_track_t ;
typedef  int /*<<< orphan*/  demuxer_t ;
struct TYPE_10__ {scalar_t__ pts; int keyframe; scalar_t__ pos; } ;
typedef  TYPE_3__ demux_packet_t ;
struct TYPE_11__ {TYPE_1__* codec; } ;
struct TYPE_8__ {char* codec; int block_align; } ;

/* Variables and functions */
 scalar_t__ MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  add_packet (int /*<<< orphan*/ *,TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 TYPE_3__* new_demux_packet_from (int*,int) ; 
 int** sipr_swaps ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  talloc_free (struct demux_packet*) ; 

__attribute__((used)) static bool handle_realaudio(demuxer_t *demuxer, mkv_track_t *track,
                             struct demux_packet *orig)
{
    uint32_t sps = track->sub_packet_size;
    uint32_t sph = track->sub_packet_h;
    uint32_t cfs = track->coded_framesize; // restricted to [1,0x40000000]
    uint32_t w = track->audiopk_size;
    uint32_t spc = track->sub_packet_cnt;
    uint8_t *buffer = orig->buffer;
    uint32_t size = orig->len;
    demux_packet_t *dp;
    // track->audio_buf allocation size
    size_t audiobuf_size = sph * w;

    if (!track->audio_buf || !track->audio_timestamp || !track->stream)
        return false;

    const char *codec = track->stream->codec->codec ? track->stream->codec->codec : "";
    if (!strcmp(codec, "ra_288")) {
        for (int x = 0; x < sph / 2; x++) {
            uint64_t dst_offset = x * 2 * w + spc * (uint64_t)cfs;
            if (dst_offset + cfs > audiobuf_size)
                goto error;
            uint64_t src_offset = x * (uint64_t)cfs;
            if (src_offset + cfs > size)
                goto error;
            memcpy(track->audio_buf + dst_offset, buffer + src_offset, cfs);
        }
    } else if (!strcmp(codec, "cook") || !strcmp(codec, "atrac3")) {
        for (int x = 0; x < w / sps; x++) {
            uint32_t dst_offset =
                sps * (sph * x + ((sph + 1) / 2) * (spc & 1) + (spc >> 1));
            if (dst_offset + sps > audiobuf_size)
                goto error;
            uint32_t src_offset = sps * x;
            if (src_offset + sps > size)
                goto error;
            memcpy(track->audio_buf + dst_offset, buffer + src_offset, sps);
        }
    } else if (!strcmp(codec, "sipr")) {
        if (spc * w + w > audiobuf_size || w > size)
            goto error;
        memcpy(track->audio_buf + spc * w, buffer, w);
        if (spc == sph - 1) {
            int n;
            int bs = sph * w * 2 / 96;      // nibbles per subpacket
            // Perform reordering
            for (n = 0; n < 38; n++) {
                unsigned int i = bs * sipr_swaps[n][0]; // 77 max
                unsigned int o = bs * sipr_swaps[n][1]; // 95 max
                // swap nibbles of block 'i' with 'o'
                for (int j = 0; j < bs; j++) {
                    if (i / 2 >= audiobuf_size || o / 2 >= audiobuf_size)
                        goto error;
                    uint8_t iv = track->audio_buf[i / 2];
                    uint8_t ov = track->audio_buf[o / 2];
                    int x = (i & 1) ? iv >> 4 : iv & 0x0F;
                    int y = (o & 1) ? ov >> 4 : ov & 0x0F;
                    track->audio_buf[o / 2] = (ov & 0x0F) | (o & 1 ? x << 4 : x);
                    track->audio_buf[i / 2] = (iv & 0x0F) | (i & 1 ? y << 4 : y);
                    i++;
                    o++;
                }
            }
        }
    } else {
        // Not a codec that requires reordering
        return false;
    }

    track->audio_timestamp[track->sub_packet_cnt] =
        track->ra_pts == orig->pts ? 0 : orig->pts;
    track->ra_pts = orig->pts;

    if (++(track->sub_packet_cnt) == sph) {
        track->sub_packet_cnt = 0;
        // apk_usize has same range as coded_framesize in worst case
        uint32_t apk_usize = track->stream->codec->block_align;
        if (apk_usize > audiobuf_size)
            goto error;
        // Release all the audio packets
        for (int x = 0; x < sph * w / apk_usize; x++) {
            dp = new_demux_packet_from(track->audio_buf + x * apk_usize,
                                        apk_usize);
            if (!dp)
                goto error;
            /* Put timestamp only on packets that correspond to original
             * audio packets in file */
            dp->pts = (x * apk_usize % w) ? MP_NOPTS_VALUE :
                track->audio_timestamp[x * apk_usize / w];
            dp->pos = orig->pos + x;
            dp->keyframe = !x;   // Mark first packet as keyframe
            add_packet(demuxer, track->stream, dp);
        }
    }

error:
    talloc_free(orig);
    return true;
}