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
struct TYPE_5__ {int /*<<< orphan*/  av_parser_codec; int /*<<< orphan*/ * av_parser; } ;
typedef  TYPE_1__ mkv_track_t ;
struct TYPE_6__ {int num_tracks; int num_blocks; int num_packets; int /*<<< orphan*/  skip_to_timecode; int /*<<< orphan*/ * packets; int /*<<< orphan*/ * blocks; TYPE_1__** tracks; } ;
typedef  TYPE_2__ mkv_demuxer_t ;
struct TYPE_7__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MIN ; 
 int /*<<< orphan*/  av_parser_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mkv_seek_reset(demuxer_t *demuxer)
{
    mkv_demuxer_t *mkv_d = demuxer->priv;

    for (int i = 0; i < mkv_d->num_tracks; i++) {
        mkv_track_t *track = mkv_d->tracks[i];
        if (track->av_parser)
            av_parser_close(track->av_parser);
        track->av_parser = NULL;
        avcodec_free_context(&track->av_parser_codec);
    }

    for (int n = 0; n < mkv_d->num_blocks; n++)
        free_block(&mkv_d->blocks[n]);
    mkv_d->num_blocks = 0;

    for (int n = 0; n < mkv_d->num_packets; n++)
        talloc_free(mkv_d->packets[n]);
    mkv_d->num_packets = 0;

    mkv_d->skip_to_timecode = INT64_MIN;
}