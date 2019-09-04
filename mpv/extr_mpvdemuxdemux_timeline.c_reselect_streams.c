#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct virtual_stream {int selected; int /*<<< orphan*/  sh; } ;
struct sh_stream {int dummy; } ;
struct segment {int num_stream_map; scalar_t__ d; size_t* stream_map; } ;
struct priv {int num_streams; int num_segments; TYPE_1__* current; struct virtual_stream** streams; struct segment** segments; } ;
struct demuxer {struct priv* priv; } ;
struct TYPE_2__ {scalar_t__ d; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 struct sh_stream* demux_get_stream (scalar_t__,int) ; 
 int demux_stream_is_selected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demuxer_select_track (scalar_t__,struct sh_stream*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reselect_streams(struct demuxer *demuxer)
{
    struct priv *p = demuxer->priv;

    for (int n = 0; n < p->num_streams; n++) {
        struct virtual_stream *vs = p->streams[n];
        vs->selected = demux_stream_is_selected(vs->sh);
    }

    for (int n = 0; n < p->num_segments; n++) {
        struct segment *seg = p->segments[n];
        for (int i = 0; i < seg->num_stream_map; i++) {
            if (!seg->d)
                continue;

            struct sh_stream *sh = demux_get_stream(seg->d, i);
            bool selected = false;
            if (seg->stream_map[i] >= 0)
                selected = p->streams[seg->stream_map[i]]->selected;
            // This stops demuxer readahead for inactive segments.
            if (!p->current || seg->d != p->current->d)
                selected = false;
            demuxer_select_track(seg->d, sh, MP_NOPTS_VALUE, selected);
        }
    }
}