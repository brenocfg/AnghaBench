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
struct demux_cached_range {scalar_t__ seek_start; int num_metadata; TYPE_1__** metadata; } ;
struct TYPE_3__ {scalar_t__ pts; } ;

/* Variables and functions */
 int MPMIN (int,int) ; 
 scalar_t__ MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (TYPE_1__**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (TYPE_1__*) ; 

__attribute__((used)) static void prune_metadata(struct demux_cached_range *range)
{
    int first_needed = 0;

    if (range->seek_start == MP_NOPTS_VALUE) {
        first_needed = range->num_metadata;
    } else {
        for (int n = 0; n < range->num_metadata ; n++) {
            if (range->metadata[n]->pts > range->seek_start)
                break;
            first_needed = n;
        }
    }

    // Always preserve the last entry.
    first_needed = MPMIN(first_needed, range->num_metadata - 1);

    // (Could make this significantly more efficient for large first_needed,
    // however that might be very rare and even then it might not matter.)
    for (int n = 0; n < first_needed; n++) {
        talloc_free(range->metadata[0]);
        MP_TARRAY_REMOVE_AT(range->metadata, range->num_metadata, 0);
    }
}