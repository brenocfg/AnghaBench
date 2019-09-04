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
struct segment {scalar_t__ d; int num_stream_map; int /*<<< orphan*/  url; int /*<<< orphan*/ * stream_map; int /*<<< orphan*/  d_start; int /*<<< orphan*/  start; } ;
struct priv {int num_segments; scalar_t__ dash; int /*<<< orphan*/  duration; struct segment** segments; } ;
struct demuxer {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct demuxer*,char*,...) ; 

__attribute__((used)) static void print_timeline(struct demuxer *demuxer)
{
    struct priv *p = demuxer->priv;

    MP_VERBOSE(demuxer, "Timeline segments:\n");
    for (int n = 0; n < p->num_segments; n++) {
        struct segment *seg = p->segments[n];
        int src_num = n;
        for (int i = 0; i < n - 1; i++) {
            if (seg->d && p->segments[i]->d == seg->d) {
                src_num = i;
                break;
            }
        }
        MP_VERBOSE(demuxer, " %2d: %12f [%12f] (", n, seg->start, seg->d_start);
        for (int i = 0; i < seg->num_stream_map; i++)
            MP_VERBOSE(demuxer, "%s%d", i ? " " : "", seg->stream_map[i]);
        MP_VERBOSE(demuxer, ") %d:'%s'\n", src_num, seg->url);
    }
    MP_VERBOSE(demuxer, "Total duration: %f\n", p->duration);

    if (p->dash)
        MP_VERBOSE(demuxer, "Durations and offsets are non-authoritative.\n");
}