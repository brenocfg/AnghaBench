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
struct demux_internal {int num_ranges; struct demux_cached_range** ranges; int /*<<< orphan*/  seekable_cache; } ;
struct demux_cached_range {double seek_start; double seek_end; scalar_t__ is_eof; scalar_t__ is_bof; } ;

/* Variables and functions */
 double MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  MP_VERBOSE (struct demux_internal*,char*,...) ; 
 int SEEK_FACTOR ; 

__attribute__((used)) static struct demux_cached_range *find_cache_seek_range(struct demux_internal *in,
                                                        double pts, int flags)
{
    // Note about queued low level seeks: in->seeking can be true here, and it
    // might come from a previous resume seek to the current range. If we end
    // up seeking into the current range (i.e. just changing time offset), the
    // seek needs to continue. Otherwise, we override the queued seek anyway.
    if ((flags & SEEK_FACTOR) || !in->seekable_cache)
        return NULL;

    struct demux_cached_range *res = NULL;

    for (int n = 0; n < in->num_ranges; n++) {
        struct demux_cached_range *r = in->ranges[n];
        if (r->seek_start != MP_NOPTS_VALUE) {
            MP_VERBOSE(in, "cached range %d: %f <-> %f (bof=%d, eof=%d)\n",
                       n, r->seek_start, r->seek_end, r->is_bof, r->is_eof);

            if ((pts >= r->seek_start || r->is_bof) &&
                (pts <= r->seek_end || r->is_eof))
            {
                MP_VERBOSE(in, "...using this range for in-cache seek.\n");
                res = r;
                break;
            }
        }
    }

    return res;
}