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
struct virtual_stream {scalar_t__ eos_packets; } ;
struct segment {int /*<<< orphan*/  d; scalar_t__ d_start; scalar_t__ start; int /*<<< orphan*/  index; } ;
struct priv {int num_streams; scalar_t__ eos_packets; struct virtual_stream** streams; int /*<<< orphan*/  dash; struct segment* current; } ;
struct demuxer {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct demuxer*,char*,int /*<<< orphan*/ ) ; 
 int SEEK_FORWARD ; 
 int SEEK_HR ; 
 int /*<<< orphan*/  demux_seek (int /*<<< orphan*/ ,double,int) ; 
 int /*<<< orphan*/  demux_set_ts_offset (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  reopen_lazy_segments (struct demuxer*) ; 
 int /*<<< orphan*/  reselect_streams (struct demuxer*) ; 

__attribute__((used)) static void switch_segment(struct demuxer *demuxer, struct segment *new,
                           double start_pts, int flags, bool init)
{
    struct priv *p = demuxer->priv;

    if (!(flags & SEEK_FORWARD))
        flags |= SEEK_HR;

    MP_VERBOSE(demuxer, "switch to segment %d\n", new->index);

    p->current = new;
    reopen_lazy_segments(demuxer);
    if (!new->d)
        return;
    reselect_streams(demuxer);
    if (!p->dash)
        demux_set_ts_offset(new->d, new->start - new->d_start);
    if (!p->dash || !init)
        demux_seek(new->d, start_pts, flags);

    for (int n = 0; n < p->num_streams; n++) {
        struct virtual_stream *vs = p->streams[n];
        vs->eos_packets = 0;
    }

    p->eos_packets = 0;
}