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
struct demux_internal {int dummy; } ;
struct demux_cached_range {int num_streams; int num_metadata; int /*<<< orphan*/ * metadata; int /*<<< orphan*/ * streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_seek_ranges (struct demux_cached_range*) ; 

__attribute__((used)) static void clear_cached_range(struct demux_internal *in,
                               struct demux_cached_range *range)
{
    for (int n = 0; n < range->num_streams; n++)
        clear_queue(range->streams[n]);

    for (int n = 0; n < range->num_metadata; n++)
        talloc_free(range->metadata[n]);
    range->num_metadata = 0;

    update_seek_ranges(range);
}