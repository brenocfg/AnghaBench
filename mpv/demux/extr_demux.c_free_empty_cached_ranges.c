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
struct demux_internal {int num_ranges; scalar_t__ current_range; scalar_t__* ranges; int /*<<< orphan*/  seekable_cache; } ;
struct demux_cached_range {scalar_t__ seek_start; int num_streams; scalar_t__ seek_end; struct demux_cached_range** streams; } ;

/* Variables and functions */
 int MAX_SEEK_RANGES ; 
 scalar_t__ MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (struct demux_cached_range**,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_cached_range (struct demux_internal*,struct demux_cached_range*) ; 
 int /*<<< orphan*/  talloc_free (struct demux_cached_range*) ; 

__attribute__((used)) static void free_empty_cached_ranges(struct demux_internal *in)
{
    while (1) {
        struct demux_cached_range *worst = NULL;

        int end = in->num_ranges - 1;

        // (Not set during early init or late destruction.)
        if (in->current_range) {
            assert(in->current_range && in->num_ranges > 0);
            assert(in->current_range == in->ranges[in->num_ranges - 1]);
            end -= 1;
        }

        for (int n = end; n >= 0; n--) {
            struct demux_cached_range *range = in->ranges[n];
            if (range->seek_start == MP_NOPTS_VALUE || !in->seekable_cache) {
                clear_cached_range(in, range);
                MP_TARRAY_REMOVE_AT(in->ranges, in->num_ranges, n);
                for (int i = 0; i < range->num_streams; i++)
                    talloc_free(range->streams[i]);
                talloc_free(range);
            } else {
                if (!worst || (range->seek_end - range->seek_start <
                               worst->seek_end - worst->seek_start))
                    worst = range;
            }
        }

        if (in->num_ranges <= MAX_SEEK_RANGES || !worst)
            break;

        clear_cached_range(in, worst);
    }
}