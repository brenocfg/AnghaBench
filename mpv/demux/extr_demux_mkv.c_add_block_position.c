#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct mkv_track {size_t last_index_entry; int /*<<< orphan*/  tnum; } ;
struct TYPE_6__ {scalar_t__ timecode; } ;
typedef  TYPE_1__ mkv_index_t ;
struct TYPE_7__ {int index_has_durations; int num_indexes; TYPE_1__* indexes; scalar_t__ index_complete; } ;
typedef  TYPE_2__ mkv_demuxer_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {scalar_t__ priv; } ;
typedef  TYPE_3__ demuxer_t ;

/* Variables and functions */
 int /*<<< orphan*/  cue_index_add (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void add_block_position(demuxer_t *demuxer, struct mkv_track *track,
                               uint64_t filepos,
                               int64_t timecode, int64_t duration)
{
    mkv_demuxer_t *mkv_d = (mkv_demuxer_t *) demuxer->priv;

    if (mkv_d->index_complete || !track)
        return;

    mkv_d->index_has_durations = true;

    if (track->last_index_entry != (size_t)-1) {
        mkv_index_t *index = &mkv_d->indexes[track->last_index_entry];
        // Never add blocks which are already covered by the index.
        if (index->timecode >= timecode)
            return;
    }
    cue_index_add(demuxer, track->tnum, filepos, timecode, duration);
    track->last_index_entry = mkv_d->num_indexes - 1;
}