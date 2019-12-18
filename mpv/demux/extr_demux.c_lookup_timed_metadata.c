#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timed_metadata {double pts; } ;
struct demux_internal {int cached_metadata_index; struct demux_cached_range* current_range; } ;
struct demux_cached_range {int num_metadata; struct timed_metadata** metadata; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 

__attribute__((used)) static struct timed_metadata *lookup_timed_metadata(struct demux_internal *in,
                                                    double pts)
{
    struct demux_cached_range *r = in->current_range;

    if (!r || !r->num_metadata || pts == MP_NOPTS_VALUE)
        return NULL;

    int start = 1;
    int i = in->cached_metadata_index;
    if (i >= 0 &&  i < r->num_metadata && r->metadata[i]->pts <= pts)
        start = i + 1;

    in->cached_metadata_index = r->num_metadata - 1;
    for (int n = start; n < r->num_metadata; n++) {
        if (r->metadata[n]->pts >= pts) {
            in->cached_metadata_index = n - 1;
            break;
        }
    }

    return r->metadata[in->cached_metadata_index];
}