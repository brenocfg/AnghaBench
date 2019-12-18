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
struct mkv_demuxer {int num_tracks; TYPE_2__* indexes; TYPE_1__** tracks; int /*<<< orphan*/  index_complete; } ;
struct demuxer {struct mkv_demuxer* priv; } ;
struct TYPE_5__ {scalar_t__ filepos; } ;
typedef  TYPE_2__ mkv_index_t ;
struct TYPE_4__ {int last_index_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static mkv_index_t *get_highest_index_entry(struct demuxer *demuxer)
{
    struct mkv_demuxer *mkv_d = demuxer->priv;
    assert(!mkv_d->index_complete); // would require separate code

    mkv_index_t *index = NULL;
    for (int n = 0; n < mkv_d->num_tracks; n++) {
        int n_index = mkv_d->tracks[n]->last_index_entry;
        if (n_index >= 0) {
            mkv_index_t *index2 = &mkv_d->indexes[n_index];
            if (!index || index2->filepos > index->filepos)
                index = index2;
        }
    }
    return index;
}