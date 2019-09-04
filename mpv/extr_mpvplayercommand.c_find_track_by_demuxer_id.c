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
struct track {int type; int demuxer_id; } ;
typedef  enum stream_type { ____Placeholder_stream_type } stream_type ;
struct TYPE_3__ {int num_tracks; struct track** tracks; } ;
typedef  TYPE_1__ MPContext ;

/* Variables and functions */

__attribute__((used)) static struct track *find_track_by_demuxer_id(MPContext *mpctx,
                                              enum stream_type type,
                                              int demuxer_id)
{
    for (int n = 0; n < mpctx->num_tracks; n++) {
        struct track *track = mpctx->tracks[n];
        if (track->type == type && track->demuxer_id == demuxer_id)
            return track;
    }
    return NULL;
}